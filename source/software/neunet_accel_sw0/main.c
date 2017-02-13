#include "network.h"
#include <stdio.h>

// Defines for saving/loading the network to/from a file
#define WRITE_NETWORK_TO_FILE 0
#define INIT_NETWORK_FROM_FILE 1
#define FILE_NAME "/mnt/rozipfs/trained_network.txt"

// Defines for tuning training
#define EPOCHS 50
#define MINI_BATCH_SIZE 10
#define ETA 3.0

#define CONNECT_HIDDEN_ARR(idx)     \
  float w_1_##idx[INPUT_LAYER_SIZE];  \
  w_1[idx] = w_1_##idx;

#define CONNECT_OUT_ARR(idx)      \
  float w_2_##idx[HIDDEN_NEURONS];  \
  w_2[idx] = w_2_##idx;

int main (int argc, char *argv[]) {
  #include "training_data.h"
  #include "validation_data.h"
  
  /* Setup Neural Network */ 
  network_t network;
  float *b[NUM_LAYERS];
  float b_1[HIDDEN_NEURONS];
  float b_2[OUTPUT_LAYER_SIZE];
  float **w[NUM_LAYERS];
  float *w_1[HIDDEN_NEURONS];
  float *w_2[OUTPUT_LAYER_SIZE];
  int sizes[NUM_LAYERS];
  int num_correct = 0;

  CONNECT_HIDDEN_ARR(0);
  CONNECT_HIDDEN_ARR(1);
  CONNECT_HIDDEN_ARR(2);
  CONNECT_HIDDEN_ARR(3);
  CONNECT_HIDDEN_ARR(4);
  CONNECT_HIDDEN_ARR(5);
  CONNECT_HIDDEN_ARR(6);
  CONNECT_HIDDEN_ARR(7);
  CONNECT_HIDDEN_ARR(8);
  CONNECT_HIDDEN_ARR(9);
  CONNECT_HIDDEN_ARR(10);
  CONNECT_HIDDEN_ARR(11);
  CONNECT_HIDDEN_ARR(12);
  CONNECT_HIDDEN_ARR(13);
  CONNECT_HIDDEN_ARR(14);
  CONNECT_HIDDEN_ARR(15);
  CONNECT_HIDDEN_ARR(16);
  CONNECT_HIDDEN_ARR(17);
  CONNECT_HIDDEN_ARR(18);
  CONNECT_HIDDEN_ARR(19);
  CONNECT_HIDDEN_ARR(20);
  CONNECT_HIDDEN_ARR(21);
  CONNECT_HIDDEN_ARR(22);
  CONNECT_HIDDEN_ARR(23);
  CONNECT_HIDDEN_ARR(24);
  CONNECT_HIDDEN_ARR(25);
  CONNECT_HIDDEN_ARR(26);
  CONNECT_HIDDEN_ARR(27);
  CONNECT_HIDDEN_ARR(28);
  CONNECT_HIDDEN_ARR(29);
  CONNECT_HIDDEN_ARR(30);
  CONNECT_OUT_ARR(0);
  CONNECT_OUT_ARR(1);
  CONNECT_OUT_ARR(2);
  CONNECT_OUT_ARR(3);
  CONNECT_OUT_ARR(4);
  CONNECT_OUT_ARR(5);
  CONNECT_OUT_ARR(6);
  CONNECT_OUT_ARR(7);
  CONNECT_OUT_ARR(8);
  CONNECT_OUT_ARR(9);

  b[0] = NULL; //Input layer has no weights/biases
  b[1] = b_1;
  b[2] = b_2;

  w[0] = NULL;
  w[1] = w_1;
  w[2] = w_2;

  sizes[0] = INPUT_LAYER_SIZE;
  sizes[1] = HIDDEN_NEURONS;
  sizes[2] = OUTPUT_LAYER_SIZE;

  /* Initialize the network */

  printf("Initializing the neural network\n");
  if(INIT_NETWORK_FROM_FILE){
    printf("Loading the neural network from %s\n", FILE_NAME);
    network_init_file(&network, NUM_LAYERS, sizes, b, w, FILE_NAME);
  }
  else {
    network_init(&network, NUM_LAYERS, sizes, b, w);

    /* Train Neural Network */

    //printf("Training the neural network\n");
    //SGD(network, training_data, MAX_TRAINING_SET_SIZE, EPOCHS, MINI_BATCH_SIZE, ETA);
  }

  if(USE_HW_ACCEL) {
    // Send Network to accelerator
	printf("Programming the Neural Network Accelerator\n");
	program_accelerator(network);
  }

  /* For Debug, print out contents of regs */
  volatile int * weight_h = (int*)ADDR_WEIGHT_H;
  volatile int * bias_h = (int*)ADDR_BIAS_H;
  volatile int * weight_o = (int*)ADDR_WEIGHT_O;
  volatile int * bias_o = (int*)ADDR_BIAS_O;
  volatile int * addr_ptr = (int*)ADDR_PTR;
  volatile int * layer_size = (int*)ADDR_LAYER_SIZE;

  printf("Hidden Layer Weight Ptr: %0x Bias Ptr: %0x\n", *weight_h, *bias_h);
  printf("Output Layer Weight Ptr: %0x Bias Ptr: %0x\n", *weight_o, *bias_o);
  printf("Size Hidden: %0x Size Output: %0x\n", (*layer_size) & 0x0000ffff, ((*layer_size) & 0xffff0000)>>16);
  printf("Curr Ptr: %0x\n", *addr_ptr);

  /* Evaluate Neural Network */

  printf("Evaluating the neural network\n");
  num_correct = evaluate(network, training_data, MAX_TRAINING_SET_SIZE);
  printf("Predicted %0d/%0d Correctly from Training Data.\n", num_correct, MAX_TRAINING_SET_SIZE);
  num_correct = evaluate(network, validation_data, MAX_TRAINING_SET_SIZE);
  printf("Predicted %0d/%0d Correctly from Validation Data.\n", num_correct, MAX_TRAINING_SET_SIZE);

  /* Writeback the trained network to the output file */
  if(WRITE_NETWORK_TO_FILE) {
    printf("Dumping the network to %s\n", FILE_NAME);
    network_filedump(network, FILE_NAME);
  }

  return 0;
}
