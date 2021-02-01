#include <linux/init.h>       
#include <linux/module.h>         
#include <linux/device.h>         
#include <linux/kernel.h>         
#include <linux/fs.h>             
#include <linux/uaccess.h>  
#include <linux/random.h>	//Usada para gerar os números aleatorios

// --------------------- Váriaveis Globais -----------------------------
// São declaradas estaticas para serem globais dentro do arquivo.

static int majorNumber;
static int k;
static struct class * seqClass = NULL;
static struct device * seqDev = NULL; 
static char mensagem[256] = {0};
static short tam_mensagem;
static int qtdAberturas = 0;


#define NAME "RND"
#define CLASS_NAME "RND"
MODULE_LICENSE("Dual BSD/GPL");


// --------------------- Cabeçalho das funções -------------------------

static ssize_t RND_read (struct file *, char *, size_t , loff_t *);
static int RND_open (struct inode *, struct file *);
static int RND_release (struct inode *, struct file*);
static ssize_t RND_write(struct file *, const char *, size_t , loff_t *);

static void RND_exit(void);
static int RND_init(void);


// ------------------- Estrutura com as operações de arquivos ----------

static struct file_operations fops = {	//As operações não declaradas são consideradas como NULL
	.owner = THIS_MODULE,
	.read = RND_read,
	.open = RND_open,
	.release = RND_release,
	.write = RND_write,
};

// ------------------ Funções e Métodos --------------------------------

// --- Operações com arquivo
static ssize_t RND_read (struct file * filp, char * buffer, size_t lenght, loff_t * offset){
	//k ++;
	
	int var = copy_to_user(buffer, mensagem, tam_mensagem);
	
	tam_mensagem = 0;	
	if(var == 0)
	{
		printk ("RND: Sucesso ao realizar a operação de leitura\n");
		return 0;
	}else
	{
		printk ("RND: Erro ao realizar a operação de leitura\n");
		return -EFAULT; //Caso receba um local de memória inválido
	}
	
} 

static int RND_open (struct inode * inode, struct file * file){
	qtdAberturas ++;
	printk ("RND: Arquivo aberto\n");
	printk ("RND: O arquivo foi aberto (%i) vezes\n", qtdAberturas);	
	return 0;
}

static int RND_release(struct inode * inode, struct file * filep )
{
	printk ("RND: Device Driver, fechado com sucesso\n");
	return 0;
}

static ssize_t RND_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
   k = (get_random_int() + get_random_int());
   char buf = (char) k;
   sprintf(mensagem, "%d" ,buf);   //Armazenando o que foi recebido em mensagem
   tam_mensagem = strlen(mensagem);          
   printk ("RND: Foi gerado o número (%s) pelo device Driver", mensagem);  
   printk("RND: Operação de escrita realizada com sucesso\n");
   return len;
}

// --- init e exit
static int RND_init(void)
{
	printk (KERN_ALERT "RND: Inicializando a operação do Device Driver\n");
	
	k = (get_random_int() + get_random_int());
	
	printk ("RND: K vale -> (%i)\n", k);

	
	//Alocando o major number do device driver
	majorNumber = register_chrdev (0, NAME, &fops);
	if (majorNumber < 0){
		printk ("RND: Erro ao alocar o major number para o Device Driver\n");
		return majorNumber;
	}
	printk ("RND: Alocado o major number -> (%i) para o Device Driver\n", majorNumber);
	
	
	//Registrando a classe do Device Driver
	seqClass = class_create (THIS_MODULE, CLASS_NAME);
	if (IS_ERR(seqClass)){
		unregister_chrdev (majorNumber, NAME);
		printk ("RND: Desalocado o major number do Device Driver\n");
		printk ("RND: Não foi possivel registrar a classe do Device Driver\n");

		return -1;
	}
	
	
	//Registrando o Device Driver
	seqDev = device_create(seqClass, NULL, MKDEV(majorNumber, 0), NULL, NAME);
	if(IS_ERR(seqDev)){
		class_destroy(seqClass);
		unregister_chrdev (majorNumber, NAME);
		printk ("RND: Desalocado o major number do Device Driver\n");
		printk ("RND: Não foi possivel registrar o Device Driver\n");
		return -1;
	}
	
	printk ("RND: Device Driver criado com sucesso\n");

	return 0;
}

static void RND_exit(void)
{
	//Desalocando o major number do Device Driver
	unregister_chrdev (majorNumber, NAME);
	printk ("RND: Desalocado o major number do Device Driver\n");
	
	device_destroy(seqClass, MKDEV(majorNumber, 0));     // remove the device
	class_unregister(seqClass);                          // unregister the device class
	class_destroy(seqClass); 
	
	printk(KERN_ALERT "RND: Finalizada a execução do Device Driver\n\n");
}

module_init(RND_init);
module_exit(RND_exit);

// -------- END -------




