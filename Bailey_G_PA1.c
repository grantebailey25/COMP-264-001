#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
 I Grant Bailey certify that this programming assignment reflects my own work, 
without the use of any external individuals (other than course/department staff), 
generative-AI, or any other forbidden resources. I understand/accept the consequences of 
cheating as outlined in the course syllabus.
*/

float mean(float arr[], int size);
float median(float arr[], int size);
float mode(float arr[], int size);
float std_dev(float arr[], int size);
int * rounded_vals(float arr[], int size);
char * ascii(float arr[], int size);

int main(int argc, char * argv[]) {
	float x;
	int size = argc - 1;
	float arr[size];
	float * ptr = arr;
	int index;
	for (index = 1; index <= size; index++) {
		sscanf(argv[index], "%f", &x);
		x = atof(argv[index]);
		*(ptr) = x;
		ptr++;
	}
}


float mean(float arr[], int size) {
	int index;
	float sum = 0.0;
	//Calculate the sum of all the values in the array
	for (index = 0; index < size;  index++) {
		sum = sum + arr[index];
	}
	//Calculate the precise mean
	float preciseMean = sum / size;
	//Scaling up the precise mean to single out the decimals after the 3rd, rounding to get rid of them, then scaling back down to get the true mean
	float meanVal = (round(preciseMean * 1000) / 1000); //To understand the round() function, I consulted Geeks For Geeks (geeksforgeeks.org/round-function-in-c/)
	return (meanVal);
}

float median(float arr[], int size) {
	float medianVal;
	float x;
	float y;
	float preciseMedian;
	/*Creating a sorted array, passing arr's values into it and sorting them to prepare it for median calculation.
	 I consulted Geeks For Geeks in the process of creating and understanding this sorting structure, at
	 geeksforgeeks.org/c-program-to-sort-an-array-in-ascending-order/*/
	float sortedArr[size];
	int index;
	for (index = 0; index < size; index++) {
		sortedArr[index] = arr[index];
	}
	int subIndex;
	for (index = 0; index < (size - 1); index++) {
		for (subIndex = 0; subIndex < (size - index - 1); subIndex++) {
			if (sortedArr[subIndex] > sortedArr[subIndex + 1]) {
				float temp = sortedArr[subIndex];
				sortedArr[subIndex] = sortedArr[subIndex + 1];
				sortedArr[subIndex + 1] = temp;
			}
		}
	}
	//If the size is even, integer division provides the correct median. Otherwise, average the two middle values.
	if (size % 2 == 1) {
		preciseMedian = sortedArr[size / 2];
	} else {
		x = sortedArr[size / 2];
		y = sortedArr[(size / 2) - 1];
		preciseMedian = (x + y) / 2;
	}
	//Scaling the precise median up to single out the decimals after the third, rounding to get rid of them, then scaling back down to get true median
	medianVal = (round(preciseMedian * 1000) / 1000); //(geeksforgeeks.org/round-function-in-c)
	return (medianVal);
}

float mode(float arr[], int size) {
	int index;
	int subIndex;
	int frequency;
	int maxFreq = 0;
	float modeVal = 0;
	//Finding how frequent each element of the input array is
	for (index = 0; index < size; index++) {
		frequency = 0;
		for (subIndex = 0; subIndex < size; subIndex++) {
			if (arr[index] == arr[subIndex]) {
				frequency++;
			}
		}
		//Finding the element that is most common and assigning that value to the mode
		if (frequency > maxFreq) {
			maxFreq = frequency;
			modeVal = arr[index];
		}
	}
	/*If the maximum frequency among the elements is greater than 1, then the mode is likely valid, and we can return it.
	 Otherwise, the elements likely have the same frequency and there is no true mode, so we return -1.*/
	if (maxFreq > 1) {
		return (modeVal);
	} else {
		return (-1);
	}
}
//(To get an idea on how to build the mode function, I consulted Geeks For Geeks, at geeksforgeeks.org/how-to-find-the-mode-of-numbers-in-an-array-in-c/)

float std_dev(float arr[], int size) {
	float meanVal = mean(arr, size);
	float localNumerator;
	int index;
	float localFraction;
	float sum = 0;
	float diffFromMean;
	//Find the sum of all of the numerators
	for (index = 0; index < size; index++) {
		diffFromMean = arr[index] - meanVal;
		localNumerator = (arr[index] - meanVal) * (arr[index] - meanVal);
		sum = sum + localNumerator;
	}
	//Divide the sum by the number of values - 1 and square root it
	float precise_std_dev_value = sqrt(sum / (size - 1)); // How I found out about the sqrt() function: Geeks For Geeks (geeksforgeeks.org/sqrt-function-in-c/)
	//Scaling the precise standard deviation up to single out the decimals after the third, rounding to get rid of them, then scaling back down to get the true standard deviation.
	float std_dev_value = (round(precise_std_dev_value * 1000) / 1000); //(geeksforgeeks.org/round-function-in-c)
	return (std_dev_value);
}

int * rounded_vals(float arr[], int size) {
	int roundedArr[size];
	//Initializing the pointer to the array of rounded values
	int * ptr = roundedArr;
	int index;
	//Looping through the elements of the original array, rounding them to the nearest integer, and saving them in the array of the rounded values
	for (index = 0; index < size; index++) {
		roundedArr[index] = (int) round(arr[index]); //(geeksforgeeks.org/round-function-in-c))
	}
	//Returning the pointer to the array of rounded values
	return (ptr);
}

char * ascii(float arr[], int size) {
	//Rounding all of the values of the passed array to integers
	int roundedArr[size];
	int * ptrRounded = roundedArr;
	int index;
	for(index = 0; index < size; index++) {
		*(ptrRounded) = (int) round(arr[index]);
		ptrRounded++;
	}
	//Declaring the character array to hold the ascii characters and initializing the pointer to this array
	char ascii[size];
	char * ptrAscii = ascii;
	for (index = 0; index < size; index++) {
		/*If the values of the array are within the range of the lowercase alphabet ascii values,
	 	then cast these integers to characters and save them in the ascii array.
	 	If not, save the value in the ascii array as a '*'*/
		if (roundedArr[index] >= 32 && roundedArr[index] <= 126) { 	//I assumed you are looking for the ascii range of printable characters,
			ascii[index] = (char) roundedArr[index];		//whose values I gathered from Geeks For Geeks (geeksforgeeks.org/ascii-table/)
		} else {
			ascii[index] = '*';
		}
	}
	//Return the pointer to the ascii array
	return (ptrAscii);
}
