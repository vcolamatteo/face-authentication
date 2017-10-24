#pragma once

#ifndef _LIBSVM_PREDICT_H
#define _LIBSVM_PREDICT_H

#include<string>
using namespace std;

static string label_str;

static int print_null(const char *s, ...) { return 0; }

static int(*info)(const char *fmt, ...) = &printf;

static struct svm_node *x;
static int max_nr_attr = 64;

static struct svm_model* model;
static int predict_probability = 0;

static char *_line = NULL;
static int max__line_len;

static char* read_line(FILE *input)
{
	int len;

	if (fgets(_line, max__line_len, input) == NULL)
		return NULL;

	while (strrchr(_line, '\n') == NULL)
	{
		max__line_len *= 2;
		_line = (char *)realloc(_line, max__line_len);
		len = (int)strlen(_line);
		if (fgets(_line + len, max__line_len - len, input) == NULL)
			break;
	}
	return _line;
}

static void exit_input_error(int _line_num)
{
	fprintf(stderr, "Wrong input format at _line %d\n", _line_num);
	exit(1);
}

//void predict(FILE *input, FILE *output)
static int predict(FILE *input)
{
	int correct = 0;
	int total = 0;
	double error = 0;
	double sump = 0, sumt = 0, sumpp = 0, sumtt = 0, sumpt = 0;

	int svm_type = svm_get_svm_type(model);
	int nr_class = svm_get_nr_class(model);
	double *prob_estimates = NULL;
	int j;

	if (predict_probability)
	{
		if (svm_type == NU_SVR || svm_type == EPSILON_SVR)
			info("Prob. model for test data: target value = predicted value + z,\nz: Laplace distribution e^(-|z|/sigma)/(2sigma),sigma=%g\n", svm_get_svr_probability(model));
		else
		{
			int *labels = (int *)malloc(nr_class * sizeof(int));
			svm_get_labels(model, labels);
			prob_estimates = (double *)malloc(nr_class * sizeof(double));
			//fprintf(output, "labels");
			//for (j = 0;j<nr_class;j++)
			//fprintf(output, " %d", labels[j]);
			//fprintf(output, "\n");
			free(labels);
		}
	}

	max__line_len = 1024;
	_line = (char *)malloc(max__line_len * sizeof(char));
	char* label = NULL;
	while (read_line(input) != NULL)
	{
		int i = 0;
		double target_label, predict_label;
		char *idx, *val, *endptr;
		int inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0

		label = strtok(_line, " \t\n");  label_str = label; //printf("label:    %s\n", label);
		if (label == NULL) // empty _line
			exit_input_error(total + 1);

		target_label = strtod(label, &endptr);
		if (endptr == label || *endptr != '\0')
			exit_input_error(total + 1);

		while (1)
		{
			if (i >= max_nr_attr - 1)	// need one more for index = -1
			{
				max_nr_attr *= 2;
				x = (struct svm_node *) realloc(x, max_nr_attr * sizeof(struct svm_node));
			}

			idx = strtok(NULL, ":");
			val = strtok(NULL, " \t");

			if (val == NULL)
				break;
			errno = 0;
			x[i].index = (int)strtol(idx, &endptr, 10);
			if (endptr == idx || errno != 0 || *endptr != '\0' || x[i].index <= inst_max_index)
				exit_input_error(total + 1);
			else
				inst_max_index = x[i].index;

			errno = 0;
			x[i].value = strtod(val, &endptr);
			if (endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
				exit_input_error(total + 1);

			++i;
		}
		x[i].index = -1;

		if (predict_probability && (svm_type == C_SVC || svm_type == NU_SVC))
		{
			predict_label = svm_predict_probability(model, x, prob_estimates);
			//fprintf(output, "%g", predict_label);
			//for (j = 0;j<nr_class;j++)
			//fprintf(output, " %g", prob_estimates[j]);
			//fprintf(output, "\n");
		}
		else
		{
			predict_label = svm_predict(model, x);
			//fprintf(output, "%g\n", predict_label);
		}

		if (predict_label == target_label)
			++correct;
		error += (predict_label - target_label)*(predict_label - target_label);
		sump += predict_label;
		sumt += target_label;
		sumpp += predict_label*predict_label;
		sumtt += target_label*target_label;
		sumpt += predict_label*target_label;
		++total;
	}
	if (svm_type == NU_SVR || svm_type == EPSILON_SVR)
	{
		info("Mean squared error = %g (regression)\n", error / total);
		info("Squared correlation coefficient = %g (regression)\n",
			((total*sumpt - sump*sumt)*(total*sumpt - sump*sumt)) /
			((total*sumpp - sump*sump)*(total*sumtt - sumt*sumt))
		);
	}
/*

	else {
		if (correct == 1) {  // dev calssificare un solo elemento...
			if (label_str == "0")
				info("OK: TRUE CLIENT\n");
			else
				info("OK: FAKE CLIENT\n");

		}
		if (correct == 0) {
			if (label_str == "0")
				info("WRONG: FAKE CLIENT\n");
			else
				info("WRONG: TRUE CLIENT\n");
			//		info("Accuracy = %g%% (%d/%d) (classification)\n",
			//			(double)correct / total * 100, correct, total);
		}
	}
	//info("Accuracy = %g%% (%d/%d) (classification)\n",
	//(double)correct / total * 100, correct, total);
	*/

	if (predict_probability)
		free(prob_estimates);
	
	
	return correct;
}

static void exit_with_help()
{
	printf(
		"Usage: svm-predict [options] test_file model_file output_file\n"
		"options:\n"
		"-b probability_estimates: whether to predict probability estimates, 0 or 1 (default 0); for one-class SVM only 0 is supported\n"
		"-q : quiet mode (no outputs)\n"
	);
	exit(1);
}




static int Classifier(string inputFile, svm_model *model)
{


	FILE* input=  fopen(inputFile.c_str(), "r");
	x = (struct svm_node *) malloc(max_nr_attr * sizeof(struct svm_node));
	//predict(input, output);
	int correct=predict(input);
	//svm_free_and_destroy_model(&model);
	free(x);
	free(_line);
	fclose(input);
	//fclose(output);
	
	

	return correct;
}

#endif