#include <linux/init.h>       
#include <linux/module.h>         
#include <linux/device.h>         
#include <linux/kernel.h>         
#include <linux/fs.h>             
#include <linux/uaccess.h>

//#include <openssl/e_os2.h>  
//#include <openssl/evp.h>


// --------------------- Váriaveis Globais -----------------------------
// São declaradas estaticas para serem globais dentro do arquivo.

static int majorNumber;
static int k;
static struct class * seqClass = NULL;
static struct device * seqDev = NULL; 
static char mensagem[256] = {0};
static short tam_mensagem;
static int qtdAberturas = 0;


#define NAME "SequencialN"
#define CLASS_NAME "Seq"
MODULE_LICENSE("Dual BSD/GPL");


// --------------------- Cabeçalho das funções -------------------------

static ssize_t seqN_read (struct file *, char *, size_t , loff_t *);
static int seqN_open (struct inode *, struct file *);
static int seqN_release (struct inode *, struct file*);
static ssize_t seqN_write(struct file *, const char *, size_t , loff_t *);

static void hello_exit(void);
static int hello_init(void);



// ------------------- Estrutura com as operações de arquivos ----------

static struct file_operations fops = {	//As operações não declaradas são consideradas como NULL
	.owner = THIS_MODULE,
	.read = seqN_read,
	.open = seqN_open,
	.release = seqN_release,
	.write = seqN_write,
};




// ------------------ Funções e Métodos --------------------------------

// --- Operações com arquivo
static ssize_t seqN_read (struct file * filp, char * buffer, size_t lenght, loff_t * offset){
	k ++;
	
	int var = copy_to_user(buffer, mensagem, tam_mensagem);
	
	printk ("SequencialN: Lendo o número (%s) gerado pelo Device Driver \n", mensagem);
	printk ("SequencialN: K vale -> (%i)\n", k);

	tam_mensagem = 0;	
	if(var == 0)
	{
		printk ("SequencialN: Sucesso ao realizar a operação de leitura\n");
		return k;
	}else
	{
		printk ("SequencialN: Erro ao realizar a operação de leitura\n");
		return -EFAULT; //Caso receba um local de memória inválido
	}
	
} 

static int seqN_open (struct inode * inode, struct file * file){
	qtdAberturas ++;
	printk ("SequencialN: Arquivo aberto\n");
	printk ("SequencialN: O arquivo foi aberto (%i) vezes\n",  qtdAberturas);	
	return 0;
}

static int seqN_release(struct inode * inode, struct file * filep )
{
	printk ("SequencialN: Device Driver, fechado com sucesso\n");
	return 0;
}

static ssize_t seqN_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
   char buf = (char)k;
   sprintf(mensagem, "%d" ,buf);   //Armazenando o que foi recebido em mensagem
   tam_mensagem = strlen(mensagem);          
   printk ("SequencialN: Escrevendo o número -> (%s) gerado pelo Device Driver", mensagem);  
   printk ("SequencialN: Operação de escrita realizada com sucesso\n");
   return len;
}

// --- init e exit
static int hello_init(void)
{
	printk (KERN_ALERT "SequencialN: Inicializando a operação do Device Driver\n");
	
	k = 0;
	
	//Alocando o major number do device driver
	majorNumber = register_chrdev (0, NAME, &fops);
	if (majorNumber < 0){
		printk ("SequencialN: Erro ao alocar o major number para o Device Driver\n");
		return majorNumber;
	}
	printk ("SequencialN: Alocado o major number -> (%i) para o Device Driver\n", majorNumber);
	
	
	//Registrando a classe do Device Driver
	seqClass = class_create (THIS_MODULE, CLASS_NAME);
	if (IS_ERR(seqClass)){
		unregister_chrdev (majorNumber, NAME);
		printk ("SequencialN: Desalocado o major number do Device Driver\n");
		printk ("SequencialN: Não foi possivel registrar a classe do Device Driver\n");

		return -1;
	}
	
	
	//Registrando o Device Driver
	seqDev = device_create(seqClass, NULL, MKDEV(majorNumber, 0), NULL, NAME);
	if(IS_ERR(seqDev)){
		class_destroy(seqClass);
		unregister_chrdev (majorNumber, NAME);
		printk ("SequencialN: Desalocado o major number do Device Driver\n");
		printk ("SequencialN: Não foi possivel registrar o Device Driver\n");
		return -1;
	}
	
	printk ("SequencialN: Device Driver criado com sucesso\n");

	return 0;
}

static void hello_exit(void)
{
	//Desalocando o major number do Device Driver
	unregister_chrdev (majorNumber, NAME);
	printk ("SequencialN: Desalocado o major number do Device Driver\n");
	
	device_destroy(seqClass, MKDEV(majorNumber, 0));     // remove the device
	class_unregister(seqClass);                          // unregister the device class
	class_destroy(seqClass); 
	
	printk(KERN_ALERT "SequencialN: Finalizada a execução do Device Driver, Adeus mundo cruel\n\n");
}


module_init(hello_init);
module_exit(hello_exit);


// -------- END -------
