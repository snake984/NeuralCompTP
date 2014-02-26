// usage : test testFile.txt network.net

#include "fann.h"

int maxIndex(fann_type *output, int size) {
  int i,indexMax=0;

  for(i=0;i<size;i++) {
    if (output[i] > output[indexMax])
      indexMax = i;
  }
  return indexMax;
}

int main(int argc , char **argv) {
  fann_type *calc_out;
  int i;
	
  if (argc==1) {
    printf("usage : test testFile.txt network.net\n");
    return 0;
  }

  struct fann_train_data *testData = fann_read_train_from_file(argv[1]);
  struct fann *ann = ann = fann_create_from_file(argv[2]);
  int output_size = fann_get_num_output(ann);

  for(i=0;i<testData->num_data ;i++) {
    // calcul du résultat de la prédiction
    calc_out = fann_run(ann, testData->input[i]);
    // interprétation et affichage du résultat		
    printf("P %d R %d\n", maxIndex(calc_out,output_size), maxIndex(testData->output[i],output_size)); 
  }        
  fann_destroy(ann);
  return 0;
}
