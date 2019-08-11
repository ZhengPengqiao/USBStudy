CFLAGS	+= -Wall `pkg-config --cflags libusb-1.0`
LDFLAGS	+= `pkg-config --libs libusb-1.0`

TARGET	:= usblist

OBJS = \
	usblist.o \
	usbshow.o

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	@echo "$@ is ready OK";

%.o:%.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o:%.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)

clean:
	@rm -rf ./*/*.o ./*.o $(TARGET)
