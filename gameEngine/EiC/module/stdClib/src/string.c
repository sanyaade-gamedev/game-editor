/* string.c
 *
 *	(C) Copyright Dec 20 1998, Edmond J. Breen.
 *		   ALL RIGHTS RESERVED.
 * This code may be copied for personal, non-profit use only.
 *
 */
/* This file is broken into 2 parts
 * the first part defines the interface routines
 * and the 2nd part adds the interface routine
 * to EiC's look up tables.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


#include "eic.h"
#include "stdliblocal.h"

#include "xalloc.h"

int checkEp(ptr_t P, int s); //maks


/*
   STRING.H STUFF
   ------------------------------*/

					      
val_t eic_memcpy(void)
{
    val_t v;
    ptr_t  p2;
    size_t s;
	int s1, s2; //maks

    getptrarg(0,v.p);
    getptrarg(1,p2);

    s = arg(2,getargs(),size_t);

    s1 = checkEp(v.p,s);
    s2 = checkEp(p2,s);

	if(s1 > 0 || s2 > 0)
	{
		s -= (s1 > s2)?s1:s2;
		if(s < 0) return v;
	}

	if(!v.p.p || !p2.p || s <= 0) return v; //maks
    
    memcpy(v.p.p,p2.p,s);
    
    return v;
}

val_t eic_memmove(void)
{
    val_t v;
    ptr_t  p2;
    size_t s;
	int s1, s2; //maks

    getptrarg(0,v.p);
    getptrarg(1,p2);

    s = arg(2,getargs(),size_t);


    s1 = checkEp(v.p,s);
    s2 = checkEp(p2,s);

	if(s1 > 0 || s2 > 0)
	{
		s -= (s1 > s2)?s1:s2;
		if(s < 0) return v;
	}
    
	if(!v.p.p || !p2.p || s <= 0) return v; //maks
    
#ifdef _SUNOS
    bcopy(p2.p,v.p.p,s);
#else
    memmove(v.p.p,p2.p,s);
#endif
    return v;
}


val_t eic_strcpy(void)     /* unsafe */
{
    val_t v;
	int s1, len; //maks
	char *src = NULL; //maks
	v.ival = 0;

    getptrarg(0,v.p);
	src = arg(1,getargs(), ptr_t).p;
	if(!src || !v.p.p) return v; //maks

	len = strlen(src);
	if(len <= 0) //maks
	{
		//Clear string
		((char *)v.p.p)[0] = 0;
		return v;
	}

	if(v.p.ep <= v.p.sp && len > 255) //maks
	{
		//Unsafe
		//May be a text in a actor struct
		//So, limit to 255 characters
		EiC_messageDisplay("Too big string in strcpy. Max string length is 255.");
	}

    s1 = checkEp(v.p, len + 1);

	if(s1 <= 0 && v.p.p)
	{
		strcpy(v.p.p, src);    
	}

    return v;
}

val_t eic_strdup(void)     /* unsafe */
{
    val_t v;
	int len; //maks
    
    char *p = arg(0,getargs(),ptr_t).p;

	v.p.ep = NULL; //maks
	if(!p) return v; //maks

    len = strlen(p);
    v.p.sp = v.p.p = xmalloc(len +1);
    if(v.p.p) {
	strcpy(v.p.p,p);
	v.p.ep = setEp(v.p, len);
    } else
	v.p.ep = NULL;

    return v;
}


val_t eic_strncpy(void)
{
    val_t v;
    ptr_t  p2;
    size_t s;
	int s1; //maks

    getptrarg(0,v.p);
    getptrarg(1,p2);

    s = arg(2,getargs(),size_t);


    
    s1 = checkEp(v.p,s);

	if(s1 > 0)
	{
		s -= s1;
	}

	if(!v.p.p || !p2.p || s <= 0) return v; //maks
    
    strncpy(v.p.p,p2.p,s);


    return v;
}
val_t eic_strcat(void)  /* unsafe */
{
    val_t v;
    ptr_t  p2;
	int s1, len; //maks

    getptrarg(0,v.p);
    getptrarg(1,p2);

	if(!v.p.p || !p2.p) return v; //maks

	len = strlen(v.p.p) + strlen(p2.p) + 1;

	if(v.p.ep <= v.p.sp && len > 255) //maks
	{
		//Unsafe
		//May be a text in a actor struct
		//So, limit to 255 characters
		EiC_messageDisplay("Too big string in strcat. Max string length is 255.");
	}

	s1 = checkEp( v.p, len ); //maks
    
	if(s1 <= 0)
	{
		strcat(v.p.p,p2.p);
	}
	
    return v;
}

val_t eic_strncat(void) /* unsafe */
{
    val_t v;
    ptr_t  p2;
    size_t s, s1;
	int s2, len; //maks
    
    getptrarg(0,v.p);
    getptrarg(1,p2);

    s = arg(2,getargs(),size_t);
    s1 = strlen(p2.p);

	if(!v.p.p || !p2.p) return v; //maks

	len = strlen(v.p.p) + (s < s1 ? s : s1) + 1;

	if(v.p.ep <= v.p.sp && len > 255) //maks
	{
		//Unsafe
		//May be a text in a actor struct
		//So, limit to 255 characters
		EiC_messageDisplay("Too big string in strncat. Max string length is 255.");
	}

    s2 = checkEp(v.p, len );
    
	if(s2 <= 0)
	{
		strncat(v.p.p,p2.p,s);
	}

    return v;
}
val_t eic_memcmp(void)
{
    val_t v;
	v.ival = 0; //maks

	if(!arg(0,getargs(),ptr_t).p || !arg(1,getargs(),ptr_t).p || arg(2,getargs(),size_t) <= 0) return v; //maks

    v.ival = memcmp(arg(0,getargs(),ptr_t).p,
		 arg(1,getargs(),ptr_t).p,
		 arg(2,getargs(),size_t));

    return v;
}
val_t eic_strcmp(void)
{
    val_t v;

	char *s1 = arg(0,getargs(),ptr_t).p;
	char *s2 = arg(1,getargs(),ptr_t).p;

	v.ival = 0;

	if(s1 && s2)
	{
		v.ival  = strcmp(s1, s2);
	}
	else if(s1)
	{
		v.ival = 1;
	}
	else if(s2)
	{
		v.ival = -1;
	}

    return v;
}

#if !defined(_WIN32_WCE) //maks
val_t eic_strcoll(void)
{
    val_t v;
    v.ival = strcoll(arg(0,getargs(),ptr_t).p,
		  arg(1,getargs(),ptr_t).p);
    return v;
}
#endif

val_t eic_strncmp(void)
{
    val_t v;
	v.ival = 0; //maks

	if(!arg(0,getargs(),ptr_t).p || !arg(1,getargs(),ptr_t).p) return v; //maks

    v.ival  = strncmp(arg(0,getargs(),ptr_t).p,
		   arg(1,getargs(),ptr_t).p,
		   arg(2,getargs(),size_t));
    return v;
}

#if !defined(_WIN32_WCE) //maks
val_t eic_strxfrm(void)
{
    val_t v;
    v.szval = strxfrm(arg(0,getargs(),ptr_t).p,
		     arg(1,getargs(),ptr_t).p,
		     arg(2,getargs(),size_t));
    return v;
}
#endif

val_t eic_memchr(void)
{
    val_t v;

    v.p = arg(0,getargs(),ptr_t);
    
    v.p.p = memchr(v.p.p,
		   arg(1,getargs(),int),
		   arg(2,getargs(),size_t));
    return v;
}
val_t eic_strchr(void)
{
    val_t v;
    v.p = arg(0,getargs(),ptr_t);

	if(!v.p.p) return v; //maks

    v.p.p = strchr(v.p.p,
	   arg(1,getargs(),int));
    return v;
}
val_t eic_strcspn(void)
{
    val_t v;
	v.szval = 0; //maks

	if(!arg(0,getargs(),ptr_t).p || !arg(1,getargs(),ptr_t).p) return v; //maks

    v.szval = strcspn(arg(0,getargs(),ptr_t).p,
		     arg(1,getargs(),ptr_t).p);
    return v;
}
val_t eic_strpbrk(void)
{
    val_t v;

    getptrarg(0,v.p);

	if(!v.p.p || !arg(1,getargs(),ptr_t).p) return v; //maks

    v.p.p = strpbrk(v.p.p,
		    arg(1,getargs(),ptr_t).p);
    return v;
}
val_t eic_strrchr(void)
{
    val_t v;
    getptrarg(0,v.p);

	if(!v.p.p) return v; //maks

    v.p.p = strrchr(v.p.p,
		    arg(1,getargs(),int));
    return v;
}
val_t eic_strspn(void)
{
    val_t v;
	v.szval = 0; //maks

	if(!arg(0,getargs(),ptr_t).p || !arg(1,getargs(),ptr_t).p) return v; //maks

    v.szval = strspn(arg(0,getargs(),ptr_t).p,
		    arg(1,getargs(),ptr_t).p);
    return v;
}
val_t eic_strstr(void)
{
    val_t v;
    getptrarg(0,v.p);

	if(!v.p.p || !arg(1,getargs(),ptr_t).p) return v; //maks
    
    v.p.p = strstr(v.p.p,
		   arg(1,getargs(),ptr_t).p);
    return v;
}
val_t eic_strtok(void)
{
    static val_t h;
    val_t v;

    getptrarg(0,v.p);

    if(v.p.p == NULL) {
	v.p.sp = h.p.sp;
	v.p.ep = h.p.ep;
    }else
	h.p = v.p;
    
    v.p.p = strtok(v.p.p,
		   arg(1,getargs(),ptr_t).p);
    return v;
}
val_t eic_memset(void)
{
    val_t v;
    size_t s;
	int s1; //maks

    getptrarg(0,v.p);
    
    s = arg(2,getargs(),size_t);
    s1 = checkEp(v.p,s);

	if(s1 > 0)
	{
		s -= s1;
	}

	if(!v.p.p || !arg(1,getargs(),int) || s <= 0) return v; //maks

    memset(v.p.p,
	   arg(1,getargs(),int),
	   s);
    return v;
}

#if !defined(_WIN32_WCE) //maks
val_t eic_strerror(void)
{
    val_t v;
    
    v.p.p = strerror(arg(0,getargs(),int));

    v.p.sp = v.p.p;
    
    setEp( v.p, strlen(v.p.p) + 1 );
    
    return v;
}
#endif

val_t eic_strlen(void)
{
    val_t v;
	v.szval = 0; //maks

	if(!arg(0,getargs(),ptr_t).p) return v; //maks

    v.szval = strlen(arg(0,getargs(),ptr_t).p);
    return v;
}


val_t eic_strrev(void)
{
    val_t v;
    getptrarg(0,v.p);
    v.p.p = strrev(v.p.p);
    return  v;
}

val_t eic_fftoa(void)
{
    val_t v;
    arg_list ap = getargs();

    getptrarg(1,v.p);
    
    fftoa(arg(0,ap,float),   /* value */
	  v.p.p,             /* string */
	  arg(2,ap,int),     /* precision */
	  arg(3,ap,char),    /* 'f','e' or 'E' */
	  arg(4,ap,int));    /* truncation, i.e. 0 or 1 */
    return v;
}



/********************************************************************/

void module_string(void) //maks
{

    /* string .h */
    EiC_add_builtinfunc("memcpy",eic_memcpy);
    EiC_add_builtinfunc("memmove",eic_memmove);
	EiC_add_builtinfunc("memcmp",eic_memcmp);
	EiC_add_builtinfunc("memset",eic_memset);

    EiC_add_builtinfunc("strcpy",eic_strcpy);
    //EiC_add_builtinfunc("strdup",eic_strdup);
    EiC_add_builtinfunc("strncpy",eic_strncpy);
    EiC_add_builtinfunc("strcat",eic_strcat);
    EiC_add_builtinfunc("strncat",eic_strncat);
    
    EiC_add_builtinfunc("strcmp",eic_strcmp);
    //EiC_add_builtinfunc("strcoll",eic_strcoll);
    EiC_add_builtinfunc("strncmp",eic_strncmp);
    //EiC_add_builtinfunc("strxfrm",eic_strxfrm);
    //EiC_add_builtinfunc("memchr",eic_memchr);
    EiC_add_builtinfunc("strchr",eic_strchr);
    EiC_add_builtinfunc("strcspn",eic_strcspn);
    //EiC_add_builtinfunc("strpbrk",eic_strpbrk);
    /*EiC_add_builtinfunc("strrchr",eic_strrchr);
    EiC_add_builtinfunc("strspn",eic_strspn);
    EiC_add_builtinfunc("strstr",eic_strstr);
    EiC_add_builtinfunc("strtok",eic_strtok);    
    EiC_add_builtinfunc("strerror",eic_strerror);*/
    EiC_add_builtinfunc("strlen",eic_strlen);
    
    /*EiC_add_builtinfunc("strrev", eic_strrev);
    EiC_add_builtinfunc("fftoa", eic_fftoa);*/

}
