CFLAGS := `pkg-config libpng --cflags` -std=c99 -Werror -Wpedantic -Wall -Wextra -c
LFLAGS := `pkg-config libpng --libs` 
OBJDIR := objdir
OBJS := $(addprefix $(OBJDIR)/,test0.o png_wrapper.o)

$(OBJDIR)/%.o : %.c
	gcc $< -o $@ $(CFLAGS) $(OUTPUT_OPTIONS)

test0: $(OBJS)
	gcc $(OBJS) -o $@ $(LFLAGS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)


.PHONY : clean
clean:
	rm test0 $(OBJS)
	rmdir $(OBJDIR)

