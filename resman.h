#ifndef RESMAN_H
#define RESMAN_H

#define DEBUG

#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

struct _clan {
	void *res;
	void (*dealokator)(void*);
};

struct _dniz {
	struct _clan *niz;
	size_t duz;
	size_t stvduz;
};

struct _dniz *_napravi_dniz() {
	struct _dniz *p = malloc(sizeof(*p));
	if(!p)
		return NULL;
	p->duz = 0;
	p->stvduz = 8;
	p->niz = malloc(p->stvduz*sizeof(*p->niz));
	if(!p->niz)
		return NULL;
	return p;
}

void _oslobodi_dniz(struct _dniz *niz) {
	free(niz->niz);
	free(niz);
}

int _dodaj_dniz(struct _dniz* niz, struct _clan c) {
	if(niz->duz == niz->stvduz) {
		struct _clan *p = reallocarray(niz->niz, niz->stvduz*=2, sizeof(*niz->niz));
		if(!p)
			return -1;
		niz->niz = p;
	}
	niz->niz[niz->duz++] = c;

	return 0;
}

struct resman {
	struct _dniz dniz;
};

struct resman *init_resman() {
	return (struct resman*)_napravi_dniz();
}

int dodaj_resman(struct resman *rm, void *p, void (*f)(void*)) {
	struct _clan c;
	c.res = p;
	c.dealokator = f;
	return _dodaj_dniz((struct _dniz*)rm, c);
}

void oslobodi_resman(struct resman *rm) {
	struct _dniz *niz = (struct _dniz*)rm;
	for(int i = niz->duz-1; i >= 0 ; i--)
		(niz->niz[i].dealokator)(niz->niz[i].res);
	_oslobodi_dniz(niz);
}

#endif /* RESMAN_H */
