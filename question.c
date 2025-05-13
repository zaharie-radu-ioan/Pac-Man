#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "question.h"

typedef struct
{
    char question[1024];
    char answer;
} Question;

extern int score; // sa nu accesezi direct fără această linie dacă score e în alt fișier

Question questions[] = {
    //==========================================TOPIC 11=========================================
    {"What is the ability of machines to perform tasks that would normally require human intelligence?\nA. Artificial intelligence\nB. Data science\nC. Data learning\nD. Machine intelligence", 'A'},

    {"What is the name of the field of AI that focuses on developing algorithms to extract information from images and videos?\nA. Computer vision\nB. Natural language processing\nC. Video translation\nD. None of the answers", 'A'},

    {"What is the most important thing to keep in mind when developing and deploying AI systems?\nA. All the answers\nB. AI systems should be aligned with human values\nC. AI systems need to be transparent and accountable\nD. AI systems should be made to be fair and unbiased", 'A'},

    {"What is the most important thing that we need to do to ensure that AI is accessible to everyone?\nA. All the answers\nB. Invest in education and training to ensure that everyone has the skills and knowledge to use AI\nC. Promote the responsible development and use of AI\nD. Develop affordable and accessible AI tools and resources", 'A'},

    {"What is the future of AI?\nA. All the answers\nB. AI will be used to replace humans for manual tasks\nC. AI will be used to solve challenges that humans can’t\nD. AI will become a big part of our lives", 'A'},

    {"What is artificial intelligence (AI)?\nA. All the rest\nB. The ability of machines to mimic human behavior.\nC. The ability of machines to think and learn like humans.\nD. The ability of machines to perform tasks that would normally require human input.", 'A'},

    {"What is the name of the field of AI that focuses on developing algorithms to understand and generate natural language?\nA. Natural language processing (NLP)\nB. Speech recognition\nC. Computer vision\nD. None of the answers", 'A'},

    {"What type of AI algorithm can be used for ads?\nA. Recommendation engine\nB. Guess engine\nC. Ads learning\nD. Tracking engine", 'A'},

    {"Which of the following is NOT a potential benefit of AI?\nA. Making certain jobs not needed anymore\nB. Increasing productivity\nC. Creating new products and services\nD. Improving decision making", 'A'},

    {"Which of the following is NOT a way to measure the success of an AI system?\nA. Social impact\nB. Recall\nC. Accuracy\nD. Precision", 'A'},

    // Set 3 — Machine Learning
    {"Which of the following is a type of supervised learning?\nA. Regression\nB. Unsupervised learning\nC. Dimensionality reduction\nD. Reinforcement learning", 'A'},

    {"Which of the following occurs when a model learns the training data too well and is unable to generalize to new data?\nA. Overfitting\nB. Guessing\nC. Underfitting\nD. Overestimating", 'A'},

    {"What is the input for a machine learning model?\nA. Data\nB. Parameters\nC. Commands\nD. Code", 'A'},

    {"What is the output of a machine learning model?\nA. Prediction\nB. Estimation\nC. Data\nD. Variables", 'A'},

    {"What type of machine learning model is given labeled data?\nA. Supervised learning\nB. Deep learning\nC. Unsupervised learning\nD. Reinforcement learning", 'A'},

    // Set 4 — ML fundamentals
    {"Which of the following is a field of study that gives computers the ability to learn without being explicitly programmed?\nA. Machine learning\nB. Database programming\nC. Data mining\nD. Web programming", 'A'},

    {"What is the output of a machine learning algorithm?\nA. A model\nB. A hypothesis\nC. An educated guess\nD. A feature", 'A'},

    {"Which type of machine learning does not receive labeled data?\nA. Unsupervised learning\nB. Semi-supervised learning\nC. Reinforcement learning\nD. Supervised learning", 'A'},

    {"Which of the following is a parameter that is set before the training of a machine learning model?\nA. Hyperparameter\nB. Label\nC. Feature\nD. Instance", 'A'},

    {"Which of the following is a set of data used to tune the hyperparameters of a machine learning model?\nA. Validation set\nB. Training set\nC. Development set\nD. Testing set", 'A'},

    // Set 5 — Deep Learning
    {"Which of the following is NOT a type of deep learning?\nA. Random Forest Logic\nB. Generative Adversarial Network\nC. Recurrent Neural Network\nD. Convolutional Neural Network", 'A'},

    {"Which of the following domains can benefit from deep learning?\nA. All the rest\nB. Medicine\nC. Financial sector\nD. Car industry", 'A'},

    {"Which deep learning technique is best suited for image recognition tasks?\nA. Convolutional Neural Network\nB. Autoencoder\nC. Recurrent Neural Network\nD. Generative Adversarial Network", 'A'},

    {"Which deep learning technique is best suited for language interpretation tasks?\nA. Recurrent Neural Network\nB. Generative Adversarial Network\nC. Convolutional Neural Network\nD. Autoencoder", 'A'},

    {"What does deep learning mean?\nA. A type of machine learning that uses artificial neural networks with multiple layers to learn from data\nB. A type of machine learning that is used only for hard tasks\nC. A type of machine learning that does not use neural networks\nD. A type of machine learning that uses only high volumes of data", 'A'},

    // Set 6 — Neural Networks
    {"Which one is the basic part of an artificial neural network?\nA. Neuron\nB. Layer\nC. Weight\nD. Function", 'A'},

    {"Which one is the layer that receives data to feed the neural network?\nA. Input layer\nB. Output layer\nC. Hidden layer\nD. Outside layer", 'A'},

    {"Which of the following is a type of machine learning that uses artificial neural networks with multiple hidden layers?\nA. Deep learning\nB. Supervised learning\nC. Layer learning\nD. Reinforcement learning", 'A'},

    {"Which of the below is a challenge for deep learning?\nA. Explainability\nB. Cost\nC. Finding data\nD. Finding people who can create the programs", 'A'},

    {"Which of the following is a type of deep learning model?\nA. Convolutional Neural Networks\nB. k-Nearest Neighbors\nC. Support Vector Machine\nD. Logistic Regression", 'A'},

    // Bias in AI
    {"How can we mitigate bias in AI?\nA. use a diverse dataset\nB. use more data\nC. use biased data\nD. use less data", 'A'},

    {"What possible consequences can bias in AI lead to?\nA. discrimination\nB. efficiency\nC. accuracy\nD. transparency", 'A'},

    {"What is the main cause of bias in AI programming?\nA. data bias\nB. human bias\nC. algorithmic bias\nD. judgment bias", 'A'},

    {"Which of the following is NOT an example of algorithmic bias in AI?\nA. A search engine that is more likely to return results for popular websites than for less popular websites.\nB. A spam filter that is more likely to flag emails from women than from men.\nC. A resume screening algorithm that is more likely to recommend male candidates for high-paying jobs than female candidates.\nD. A facial recognition algorithm that is more accurate at identifying white people than black people.", 'A'},

    {"Which can be an option to avoid bias in AI-powered decisions?\nA. have human oversight\nB. don’t use AI to take those decisions\nC. create a separate AI to validate the first one\nD. only use AI for small decisions", 'A'},

    {"Which one is a way to mitigate bias in AI?\nA. Create audit systems for bias\nB. Don’t use the products\nC. Highlight the bias and ignore it\nD. Don’t question the output of the application", 'A'},

    {"What is a possible consequence of bias in AI?\nA. Unfair outcomes\nB. Transparent outcomes\nC. Good enough outcomes\nD. Accurate outcomes", 'A'},

    {"What is a correct definition for bias in AI?\nA. Bias in AI programming can lead to apps that favor a certain group of people or certain result\nB. Bias in AI programming can lead to apps that make mistakes\nC. Bias in AI programming can lead to apps that are inefficient\nD. Bias in AI programming can lead to apps created only for a certain situation", 'A'},

    {"What is a cause of bias in AI?\nA. All the rest\nB. Data used to train the AI is not representative\nC. The AI inherits the bias of the programmers\nD. The AI is too rudimentary to differentiate human nuances", 'A'},

    {"Who is responsible for fighting and mitigating bias in AI programming?\nA. All the rest\nB. The programmers\nC. The private companies\nD. The public sector", 'A'},

    // Privacy in AI

    {"Which of the following is a benefit of using AI to protect privacy?\nA. all the rest\nB. AI tools can be used to develop new encryption algorithms\nC. AI tools can be used to identify and remove personally identifiable information\nD. AI tools can be used to discover data breaches", 'A'},

    {"Which of the following is NOT a type of privacy-preserving AI?\nA. Centralized learning\nB. Differential privacy\nC. Federated learning\nD. Secure multi-party computation", 'A'},

    {"What is the most important thing to keep in mind when thinking about privacy in AI?\nA. Before releasing an AI product we need to prioritize the privacy elements\nB. Privacy is not mandatory\nC. Privacy is just a module\nD. Privacy concerns only matter when users complain", 'A'},

    {"Which of the following is a challenge to implementing privacy-preserving AI?\nA. All the rest\nB. Need to educate developers and users\nC. Need to develop new algorithms\nD. Trade-offs between privacy and accuracy", 'A'},

    {"What is the difference between PII and non-PII?\nA. PII identifies individuals, non-PII does not\nB. PII is used by businesses, non-PII by governments\nC. PII is public, non-PII is private\nD. PII is online data, non-PII is offline data", 'A'},

    {"Which of the following is NOT a privacy-preserving AI practice?\nA. Data sharing\nB. Data anonymization\nC. Data minimization\nD. Differential privacy", 'A'},

    {"Which is an example of privacy-preserving AI?\nA. An assistant that responds to natural language\nB. Facial recognition on the street\nC. Recommender system from past purchases\nD. All the other options", 'A'},

    {"Which is NOT a way to address privacy concerns?\nA. Using AI to gather more data\nB. Developing transparent AI\nC. Giving users control over their data\nD. Creating privacy laws", 'A'},

    {"What is a privacy-preserving AI principle?\nA. Using AI to process data to protect individual privacy\nB. Using AI to discriminate\nC. Using AI to collect maximum data\nD. Using AI to decide without consent", 'A'},

    {"What is a risk of AI-powered social media products?\nA. All the rest\nB. Tracking users without consent\nC. Personalized content without knowledge\nD. Deep fakes spreading misinformation", 'A'},

    // Transparency in AI
    {"Which is NOT a benefit of transparency in AI ethics?\nA. It makes AI systems more accurate\nB. Helps mitigate ethical risks\nC. Builds trust in AI\nD. Ensures responsible use", 'A'},

    {"Which is NOT a challenge to achieving transparency?\nA. Developers are reluctant to share info\nB. No standard for AI transparency\nC. Complex systems hard to explain\nD. No universal solution", 'A'},

    {"Which is a transparency-enhancing measure?\nA. All other answers\nB. Publish technical documentation\nC. Provide training data access\nD. Develop explainable AI tools", 'A'},

    {"Which is NOT expected from an ethical reviewer?\nA. Approving/rejecting AI for release\nB. Detect transparency issues\nC. Guide AI development\nD. Document transparency process", 'A'},

    {"What promotes transparency in AI ethics?\nA. All other answers\nB. Accountability\nC. Educating users\nD. Creating transparency playbooks", 'A'},

    {"Which is NOT a way to measure transparency?\nA. Public’s understanding of AI\nB. Number of systems reviewed\nC. Published AI ethics papers\nD. Developers’ understanding", 'A'},

    {"Which is NOT a cost of transparency?\nA. Increased trust\nB. Reduced accuracy\nC. Higher development cost\nD. Privacy risks", 'A'},

    {"Which is NOT a way to make AI explainable?\nA. All other answers\nB. Create visualization tools\nC. Use smaller data samples\nD. Use simple algorithms", 'A'},

    {"What is the best way to ensure transparency?\nA. Hybrid: governments, NGOs, and industry together\nB. Top-down by governments\nC. Don’t regulate\nD. Bottom-up by companies", 'A'},

    {"Which is NOT a challenge to transparency?\nA. All the rest\nB. Lack of expertise\nC. Lack of resources\nD. Lack of time", 'A'}};

int question_count = sizeof(questions) / sizeof(questions[0]);
int shuffled_indexes[100];
int current_question_index = 0;

void shuffle_questions()
{
    for (int i = 0; i < question_count; i++)
        shuffled_indexes[i] = i;

    for (int i = question_count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = shuffled_indexes[i];
        shuffled_indexes[i] = shuffled_indexes[j];
        shuffled_indexes[j] = temp;
    }
}

int handleQuestion()
{
    if (current_question_index >= question_count)
    {
        printf("Ai terminat toate întrebările!\n");
        return 1;
    }

    int q_index = shuffled_indexes[current_question_index++];
    printf("\n%s\n", questions[q_index].question);
    printf("Raspuns: ");
    fflush(stdout); // fara asta nu vezi întrebarea

    char r;
    if (scanf(" %c", &r) != 1)
        return 0;

    if (toupper(r) == questions[q_index].answer)
    {
        printf("Corect!\n");
        return 1;
    }
    else
    {
        printf("Gresit! Raspunsul era: %c\n", questions[q_index].answer);
        return 0;
    }
}
