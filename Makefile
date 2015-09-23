CFLAGS := `pkg-config libpng --cflags` -Werror -Wpedantic -Wall -Wextra -c
LFLAGS := `pkg-config libpng --libs` 
OBJDIR := objdir
LIBS_OBJS := $(addprefix $(OBJDIR)/, png_wrapper.o)
TEST0_OBJS := $(LIBS_OBJS) $(addprefix $(OBJDIR)/, test0.o)
RAY0_OBJS := $(LIBS_OBJS) $(addprefix $(OBJDIR)/, ray0.o)

$(OBJDIR)/%.o : %.cpp
	gcc $< -o $@ $(CFLAGS) $(OUTPUT_OPTIONS)

all: test0 ray0

test0: $(TEST0_OBJS)
	gcc $(TEST0_OBJS) -o $@ $(LFLAGS)

ray0: $(RAY0_OBJS)
	g++ $(RAY0_OBJS) -o $@ $(LFLAGS)


$(LIBS_OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)


.PHONY : clean
clean:
	rm test0 $(LIBS_OBJS)
	rmdir $(OBJDIR)

