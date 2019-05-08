all: linked_list.o path.o errors.o parse.o redir.o cmd.o job.o wish.o wish

linked_list.o: linked_list.h linked_list.c
	gcc -c linked_list.c
path.o: linked_list.h path.h path.c
	gcc -c path.c

errors.o: errors.h errors.c
	gcc -c errors.c

parse.o: parse.h parse.c
	gcc -c parse.c
redir.o: parse.h redir.h redir.c
	gcc -c redir.c
cmd.o: parse.h path.h cmd.h cmd.c
	gcc -c cmd.c
job.o: parse.h redir.h cmd.h path.h errors.h job.h job.c
	gcc -c job.c

wish.o: parse.h errors.h job.h wish.c
	gcc -c wish.c

wish: linked_list.o path.o errors.o parse.o redir.o cmd.o job.o wish.o
	gcc -o wish linked_list.o path.o errors.o parse.o redir.o cmd.o job.o wish.o