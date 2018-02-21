#	$Id: Makefile,v 1.2 2010/08/19 04:32:34 culot Exp $

SRCDIR=		.
HTABLEDIR=	../src
CC?=		gcc
LD?=		$(CC)
CFLAGS+=	-I$(HTABLEDIR) -g -Wall -Werror

SRC=		$(wildcard $(SRCDIR)/*.c)
OBJ=		$(SRC:.c=.o)
EXE=		$(SRC:.c=)
TST=		$(SRC:.c=.tst)
REF=		$(SRC:.c=.ref)
DIFF=		$(SRC:.c=.diff)

all:	$(EXE)

$(EXE):	$(SRC) $(HTABLEDIR)/htable.h
	@echo "==> Building $@"
	@$(CC) $(CFLAGS) -o $@ $(@).c

test:	$(EXE) $(TST)
	@echo
	@echo "***********************************"
	@echo "* If some regressions were found, *"
	@echo "* please review the *.diff files  *"
	@echo "***********************************"

%.tst:	%
	@printf "==> Testing $< ... "
	@./$< > $@
	-@diff -u $(<).ref $@ > $(<).diff
	-@test -s $(<).diff                                             \
		&& printf "    !!! NOT OK !!!\n"                        \
		|| (printf "OK\n" && rm -f $(<).diff)
	@rm -f $@

ref:	reference
reference: $(REF)

%.ref:	%
	@echo "==> Building reference $@"
	@$< > $@

clean:
	@rm -f $(OBJ) $(EXE) $(TST) $(DIFF) *.core
	@echo "==> Cleaning done"

clean-ref:
	@rm -f $(REF)
	@echo "==> References cleaned"

.PHONY: all test ref reference clean clean-ref

