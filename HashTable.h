#ifndef __HASH_TABLE
#define __HASH_TABLE

#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

//注意：这里的是redis实现的字典hash算法，为保证服务不被长时间占用，采用了渐进式哈希；
//同时因为内存中CPU速度不是瓶颈，因而采用了链接法

//hashFunc
#define dict_hash_function_seed 5381
unsigned int dictIntHashFunciton(unsigned int key)
{
	key += ~(key<<15);
	key ^= (key>>10);
	key += (key<<3);
	key ^= (key>>6);
	key += ~(key<<11);
	key ^= (key>>16);
	return key;
}

unsigned int dictGenCaseHashFunciton(const unsigned char* buf,int len)
{
	unsigned int hash = (unsigned int)dict_hash_function_seed;
	while(len--)
	{
		hash = ((hash<<5)+hash)+(tolower(*buf++));
	}
	return hash;
}

typedef struct hashTableEntry
{
	void* key;
	union{
		void* val;
		uint64_t u64;
		int64_t s64;
		double d;
	};
	struct hashTableEntry* next;
} hashTableEntry;

typedef struct hashTools{
	uint64_t (*hashFunction)(const void* key);
	void* (*keyDup)(void* privdata,const void* key);
	void* (*valDup)(void* privdata,const void* obj);
	int (*keyCompare)(void* privdata,const void* key1,const void* key2);
	void (*keyDestructor)(void* privdata,void* key);
	void (*valDestructor)(void* privdata,void* obj);
}hashTools;

typedef struct hashTable{
	hashTableEntry** table;
	unsigned long size;
	unsigned long sizemask;
	unsigned long used;
}hashTable;

typedef struct my_unorderede_map
{
	hashTools* tools;
	void* privdata;
	hashTable ht[2];
	long rehashIdx;
	unsigned long iterators;
}my_unorderede_map;


//declaration
void zfree(void*);


//internal func
#define IsRehashing(d) ((d)->rehashIdx != -1)
#define HashKey(d, key) (d)->tools->hashFunction(key)

static void _hashTableReset(hashTable* ht)
{
	ht->table = NULL;
	ht->size = 0;
	ht->sizemask = 0;
	ht->used = 0;
}

int rehash(my_unorderede_map* d,int n)
{
	int empty_visits = n * 10;
	if(!IsRehashing(d)) return 0;

	while(n--&&d->ht[0].used!=0)
	{
		hashTableEntry* hte,*next_hte;
		//assert(d->ht[0].size > (unsigned long) d-> rehashIdx);
		while(d->ht[0].table[d->rehashIdx] == NULL)
		{
			d->rehashIdx++;
			if(--empty_visits == 0) return 1;
		}

		hte = d->ht[0].table[d->rehashIdx];
		while(hte)
		{
			uint64_t h;
			next_hte = hte->next;

			h = HashKey(d,hte->key)&(d->ht[1].sizemask);
			hte->next = d->ht[1].table[h];
			d->ht[1].table[h] = hte;
			d->ht[1].used++;
			d->ht[0].used--;
			hte = next_hte;
		}
		d->ht[0].table[d->rehashIdx] = NULL;
		d->rehashIdx++;
	}
	if(d->ht[0].used == 0)
	{
		zfree(d->ht[0].table);
		d->ht[0] = d->ht[1];
		_hashTableReset(&d->ht[1]);
		d->rehashIdx = -1;
		return 0;
	}
	return 1;
}



//API
my_unorderede_map* CreateHashTable(hashTools* tools,void* privDataPtr)
{
	my_unorderede_map* d = (my_unorderede_map*)malloc(sizeof(*d));
	_hashTableReset(&d->ht[0]);
	_hashTableReset(&d->ht[1]);
	d->tools = tools;
	d->privdata = privDataPtr;
	d->rehashIdx = -1;
	d->iterators = 0;
	return d;
}





#endif
