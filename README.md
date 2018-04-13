# Document Classifier

## INTRODUCTION

  This project is a DOCUMENT CLASSIFIER in C that can classify text documents to the class which they belong to.
  
This project involves the concept of Machine Learning and uses Multinomial Naïve Bayes algorithm.
  
We just have to provide the training data for each class which we want to classify and the project will create the model and then classify the test document by the help of the trained document.
  
The efficiency of the project directly depends on the amount of training data.
	  

## IMPLEMENTATION

The project is a Machine Learning project implemented in C. Project functions mainly on the Multinomial Naive Bayes classifier algorithm.

### TRAINING:

First, we train our probabilistic model for which we use our training program.
The program first scans all the classes i.e. all the directories present in the current directory as each directory resembles a class. Then program makes a list of all the documents present in each class, all these files act as our training data. Then program loads a list of words from a called stop words from a file which are the words that don’t convey any meaning i.e. conjunctions, adjectives, adverbs and other words (ex- a, an, the, that, then etc.). After that point program runs through all the documents from our training data set and makes a bag of words model which is the vector of each unique word it basically contains all the unique words from all the documents and the frequency of each word in every class, the program does so by checking if a word is not a stop word or not, if the word is not a stop word we add it to our bag of words model and if the word is encountered again we increase its frequency. Next it sorts all the words in ascending order alphabetically using MERGE SORT as it is the fastest algorithm with worst case time complexity of (nlog n) compared to bubble sort whose worst-case time complexity is (n2). Now the program calculates the probability of occurrence of a each word in each class in training data set. Now we store this probabilistic model in a file. We also store the probability of each class along with the name of each class. Since, we are using dynamic memory allocation in the program for storing all the information we can scale the program to any number of classes.

### TESTING:

For testing our project, we store the test document in a file and we run another program that first loads all the stop words and then we load our trained probabilistic model. After this we go through the test document and make a list of all the words along with their frequency excluding the stop words.
Now for each word in our test document vocabulary we search probability of each word in the trained model for each class, for searching we use BINARY SEARCH because of its low time complexity. Now we can calculate the probability of the document for each class. After this point we check for the class having maximum probability and thus we can say that our test class belongs to the class with maximum probability.
The Multinomial Naive Bayes classifier algorithm goes as follows:
 
Here P(c | x) is the probability of test document x belonging to a class c.

P(c) is the probability of each class c it is given by the number of documents in a class in training set upon total number of documents in training set.

P(x) is the probability of the test document which is given by 1 upon total number of test document.

P(x | c) is the likelihood which we calculate by multiplying probability of each word given a class. Probability of each word for a class is calculated by frequency of a word in a class upon total no of words in that class (frequency(w,c))/(size(c)).

### Fine Tuning the algorithm:

The original Naive Bayes algorithm was tuned according to our necessity.
As we know P(x) in  (P(x|c)P(c))/(P(x))   will be same for every class. So, we can discard it.

Now our equation is P(x | c)×P(c).

While calculating P(x | c) if a word doesn’t occur in a class then the frequency of that word will be zero and the probability will be zero.
So, we modify our algorithm changing it to (frequency(w,c)+1)/(size(c)+|V|) here we add weight of 1 so that the numerator can be at least 1 and |v| is the size of vocabulary i.e. the total number of words in the training set.

## Results:

We trained our model on three classes namely Physics, Chemistry and Biology with 15, 9 and 10 training documents in each class.
And we where able to classify all the test documents correctly giving us an ACCURACY of 100%.

## Sources:

•	Wikipedia

•	Stanford Natural Language Processing Online Course


