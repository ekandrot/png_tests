CFLAGS := `pkg-config libpng --cflags` -Werror -Wpedantic -Wall -Wextra -std=c++0x -c
LFLAGS := `pkg-config libpng --libs` 
OBJDIR := objdir
TEST0_OBJS := $(LIBS_OBJS) $(addprefix $(OBJDIR)/, png_wrapper.o test0.o)
RAY0_OBJS := $(LIBS_OBJS) $(addprefix $(OBJDIR)/, png_wrapper.o world.o ray0.o)


all: test0 ray0

$(OBJDIR)/world.o : world.cpp world.h
	g++ $< -o $@ $(CFLAGS) $(OUTPUT_OPTIONS)

$(OBJDIR)/png_wrapper.o : png_wrapper.cpp png_wrapper.h
	g++ $< -o $@ $(CFLAGS) $(OUTPUT_OPTIONS)

$(OBJDIR)/test0.o : test0.cpp png_wrapper.h
	g++ $< -o $@ $(CFLAGS) $(OUTPUT_OPTIONS)

$(OBJDIR)/ray0.o : ray0.cpp png_wrapper.h
	g++ $< -o $@ $(CFLAGS) $(OUTPUT_OPTIONS)

test0: $(TEST0_OBJS)
	g++ $(TEST0_OBJS) -o $@ $(LFLAGS)

ray0: $(RAY0_OBJS)
	g++ $(RAY0_OBJS) -o $@ $(LFLAGS)


$(LIBS_OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

