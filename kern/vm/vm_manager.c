#include <types.h>
#include <kern/unistd.h>
#include <lib.h>
#include <vm.h>

#include <vm_manager.h>

static int page_map[MAX_RAM_SIZE/PAGE_SIZE];  //MAX_RAM_SIZE is defined in vm.h
static int initialize=1;

#define VM_ISFREE(A) A==0
static unsigned int ram_size;

/* 
 * Una mappa di interi contine il valore zero se la pagina è libera,
 * mentre contiene un valore maggiore di 0 se la pagina non è vuota.
 * Quando si richiedono N pagine la mappa corrispondente alla prima 
 * pagina assegnata conterrà il valore N. In queto modo quando verrà
 * dirchiesto di liberare il blocco con quell indirizzo è nota la 
 * dimensione del blocco
 *
 * Al primo avvio la funzione genera la mappa, ricavando il primo
 * indirizzo disponibile tramite la funzione getfirstavailable(),
 * la quale è valida solo alla prima invocazione della funzione.
 * Il valore ritornato non tiene conto infatti delle allocazioni
 * fatte da vm_manager, ma solo da ram_stealmem().
 */

paddr_t vm_allocmem(unsigned long npages){
	unsigned int i, j, counter=0;
	paddr_t addr;
	static paddr_t first;
	if(initialize){
		ram_size=ram_getsize();
		first=ram_getfirstavailable();		
		for(i=0; i<first/PAGE_SIZE; i++){
			page_map[i]=1;
		}
		for(i=first/PAGE_SIZE; i<ram_size/PAGE_SIZE; i++){
			page_map[i]=0;
		}
		initialize=0;
	}
	for(i=first/PAGE_SIZE; i<ram_size/PAGE_SIZE&&counter<npages; i++){
		if(VM_ISFREE(page_map[i])){
			if(counter==0)
				j=i;
			/* Counter for the number of pages found so far
			 * The condition counter<npages	stops the cycle
			 * when an enogh number of pages has been found.
			 */
			counter++;
		}
		else if(counter!=0)
			/* Couter has to be resetted everytime a page is found 
			 * to be already used, as a contiguos block is necessary
			 */
			counter=0;
	}
	
	if(counter<npages)			
		return 0;	
	for(i=j; i<j+npages;i++){
		/* Allocated pages are setted to 1 */
		page_map[i]=1;
	}
	/* First allocated page will contain the number of pages requested.
	 * It will be necessary to release the memory.
     */
	page_map[j]=npages;
	addr=j*PAGE_SIZE;
	return addr;
}

/* Reads in the map how many pages has been allocated and release them */
void vm_releasemem(paddr_t paddr){
	unsigned int i, k=page_map[paddr/PAGE_SIZE];
	for(i=0; i<k; i++)
		page_map[paddr/PAGE_SIZE+i]=0;
}

