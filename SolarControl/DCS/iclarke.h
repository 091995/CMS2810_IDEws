#ifndef _ICLARKE_H
#define _ICLARKE_H

struct SIClarke {
				long ds;
				long qs;
				long a;
				long b;
				long c;
				void (*calc)(struct SIClarke*);
};

typedef struct SIClarke TIClarke;

//! инициализатор по-умолчанию
#define ICLARKE_DEFAULTS { 	0, \
							0, \
							0, \
							0, \
							0, \
							iclarke_calc }

//! \memberof TClarke
void iclarke_calc(TIClarke*);

#endif

