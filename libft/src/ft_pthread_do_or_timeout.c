/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_do_or_timeout.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:36:41 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:36:51 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <pthread.h>
#include <stdio.h>
/* for ETIMEDOUT */
#include <errno.h>
#include <string.h>
#include "../inc/libft.h"

/* For clock_gettime() func that does not exist on mac */
/*
#if defined(__MACH__) && !defined(CLOCK_REALTIME)
#include <sys/time.h>
#define CLOCK_REALTIME 0
// clock_gettime is not implemented on older versions of OS X (< 10.12).
// // If implemented, CLOCK_REALTIME will have already been defined.
int clock_gettime(int clk_id, struct timespec* t) {
	struct timeval now;
	int rv = gettimeofday(&now, NULL);
	if (rv) return rv;
	t->tv_sec  = now.tv_sec;
	t->tv_nsec = now.tv_usec * 1000;
	return 0;
}
#endif*/

pthread_mutex_t calculating = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t done = PTHREAD_COND_INITIALIZER;

void				*expensive_call(void *data)
{
	//int				oldtype;
	t_pthread		*t;

	pthread_cond_wait(&done, &calculating);
	//pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype); /* allow the thread to be killed at any time */
	t = (t_pthread *)data;
	//t->func(); /* calculations and expensive io here, for example: infinitely loop */
	printf("t int: %d\n", (int)t->t);
	//printf("w->extensive call: %d\n", (int)t->w->w.dist);
	//t->func(t->w); /* calculations and expensive io here, for example: infinitely loop */
	pthread_cond_signal(&done); /* wake up the caller if we've completed in time */
	return NULL;
}

/* note: this is not thread safe as it uses a global condition/mutex */
int					ft_pthread_do_or_timeout(struct timespec *max_wait, void *data)
{
	struct timespec	abs_time;
	pthread_t		tid;
	//int				err;
	t_pthread		*t;

	pthread_mutex_lock(&calculating);
	/* pthread cond_timedwait expects an absolute time to wait until */
	//clock_gettime(CLOCK_REALTIME, &abs_time);
	abs_time.tv_sec += max_wait->tv_sec;
	abs_time.tv_nsec += max_wait->tv_nsec;
	pthread_create(&tid, NULL, expensive_call, data);
	t = (t_pthread *)data;
	printf("t int first: %d\n", (int)t->t);
	/* pthread_cond_timedwait can return spuriously: this should
	 *          * be in a loop for production code
	 *                   */
	pthread_mutex_unlock(&calculating);
	/*err = pthread_cond_timedwait(&done, &calculating, &abs_time);
	if (err == ETIMEDOUT)
	{
		//t = (t_pthread *)data;
		//t->reinit(t->w);
		printf("err:%d\n", err);
		fprintf(stderr, "%s: calculation timed out\n", __func__);
	}
	if (!err)
	{
		printf("pas derreur\n");
		pthread_mutex_unlock(&calculating);
	}*/
	return 0;
}
/*
   int main()
   {
   struct timespec max_wait;

   memset(&max_wait, 0, sizeof(max_wait));
   */
/* wait at most 2 seconds */
//max_wait.tv_sec = 2;
/* wait at most 30 milliseconde = 30 000 000 de nanoseconds */
/*max_wait.tv_nsec = 30000000;
  do_or_timeout(&max_wait);

  return 0;
  }*/
