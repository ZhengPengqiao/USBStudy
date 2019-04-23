CFLAGS	+= -Wall `pkg-config --cflags libusb-1.0`
LDFLAGS	+= `pkg-config --libs libusb-1.0` -lpthread

TARGET	:= usbkeyboard

OBJS = \
	usbkeyboard.o

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
