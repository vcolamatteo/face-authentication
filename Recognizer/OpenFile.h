#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "svm.h"
#include "svm-predict.h"

static void OpenFile(string modelF) {

	const char* modelFile = modelF.c_str();
	
	

	if ((model = svm_load_model(modelFile)) == 0)
	{
		fprintf(stderr, "can't open model file %s\n", modelFile);
		system("pause");
		exit(1);
	}

	x = (struct svm_node *) malloc(max_nr_attr * sizeof(struct svm_node));
	if (predict_probability)
	{
		if (svm_check_probability_model(model) == 0)
		{
			fprintf(stderr, "Model does not support probabiliy estimates\n");
			system("pause");
			exit(1);
		}
	}
	else
	{
		if (svm_check_probability_model(model) != 0)
			info("Model supports probability estimates, but disabled in prediction.\n");
	}

}
