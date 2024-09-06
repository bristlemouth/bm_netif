typedef struct {
  void (*const receive)(void *self, unsigned char *data, unsigned int length);
} ReceiverTrait;

typedef struct {
  void *self;
  ReceiverTrait const *trait;
} Receiver;
