    #include "raylib.h"
    #include <string.h>
    #include <ctype.h>
    #include <stdlib.h>
    #include <stdio.h>

    #define MAX_QUESTIONS 100

    typedef struct {
        char question[1024];
        char answer;
    } Question;

    extern int score;
    extern int lives;
    extern char map1[15][21];
    extern bool game_over;

    static Question questions[MAX_QUESTIONS];
    static int question_count = 0;
    static int shuffled_indexes[MAX_QUESTIONS];
    static int current_question_index = 0;
    static int question_active = 0;
    static int current_q = -1;
    static char selected_answer = '\0';

    void shuffle_questions() {
        for (int i = 0; i < question_count; i++) shuffled_indexes[i] = i;
        for (int i = question_count - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = shuffled_indexes[i];
            shuffled_indexes[i] = shuffled_indexes[j];
            shuffled_indexes[j] = temp;
        }
    }

    void InitQuestion() {
        question_count = 70; // doar cateva exemple
strcpy(questions[0].question, "What is the ability of machines to perform tasks that would normally require human intelligence?\nA. Artificial intelligence\nB. Data science\nC. Data learning\nD. Machine intelligence");
questions[0].answer = 'A';

strcpy(questions[1].question, "What is the name of the field of AI that focuses on developing algorithms to extract information from images and videos?\nA. Computer vision\nB. Natural language processing\nC. Video translation\nD. None of the answers");
questions[1].answer = 'A';

strcpy(questions[2].question, "What is the most important thing to keep in mind when developing and deploying AI systems?\nA. All the answers\nB. AI systems should be aligned with human values\nC. AI systems need to be transparent and accountable\nD. AI systems should be made to be fair and unbiased");
questions[2].answer = 'A';

strcpy(questions[3].question, "What is the most important thing that we need to do to ensure that AI is accessible to everyone?\nA. All the answers\nB. Invest in education and training to ensure that everyone has the skills and knowledge to use AI\nC. Promote the responsible development and use of AI\nD. Develop affordable and accessible AI tools and resources");
questions[3].answer = 'A';

strcpy(questions[4].question, "What is the future of AI?\nA. All the answers\nB. AI will be used to replace humans for manual tasks\nC. AI will be used to solve challenges that humans can’t\nD. AI will become a big part of our lives");
questions[4].answer = 'A';

strcpy(questions[5].question, "What is artificial intelligence (AI)?\nA. All the rest\nB. The ability of machines to mimic human behavior.\nC. The ability of machines to think and learn like humans.\nD. The ability of machines to perform tasks that would normally require human input.");
questions[5].answer = 'A';

strcpy(questions[6].question, "What is the name of the field of AI that focuses on developing algorithms to understand and generate natural language?\nA. Natural language processing (NLP)\nB. Speech recognition\nC. Computer vision\nD. None of the answers");
questions[6].answer = 'A';

strcpy(questions[7].question, "What type of AI algorithm can be used for ads?\nA. Recommendation engine\nB. Guess engine\nC. Ads learning\nD. Tracking engine");
questions[7].answer = 'A';

strcpy(questions[8].question, "Which of the following is NOT a potential benefit of AI?\nA. Making certain jobs not needed anymore\nB. Increasing productivity\nC. Creating new products and services\nD. Improving decision making");
questions[8].answer = 'A';

strcpy(questions[9].question, "Which of the following is NOT a way to measure the success of an AI system?\nA. Social impact\nB. Recall\nC. Accuracy\nD. Precision");
questions[9].answer = 'A';

strcpy(questions[10].question, "Which of the following is a type of supervised learning?\nA. Regression\nB. Unsupervised learning\nC. Dimensionality reduction\nD. Reinforcement learning");
questions[10].answer = 'A';

strcpy(questions[11].question, "Which of the following occurs when a model learns the training data too well and is unable to generalize to new data?\nA. Overfitting\nB. Guessing\nC. Underfitting\nD. Overestimating");
questions[11].answer = 'A';

strcpy(questions[12].question, "What is the input for a machine learning model?\nA. Data\nB. Parameters\nC. Commands\nD. Code");
questions[12].answer = 'A';

strcpy(questions[13].question, "What is the output of a machine learning model?\nA. Prediction\nB. Estimation\nC. Data\nD. Variables");
questions[13].answer = 'A';

strcpy(questions[14].question, "What type of machine learning model is given labeled data?\nA. Supervised learning\nB. Deep learning\nC. Unsupervised learning\nD. Reinforcement learning");
questions[14].answer = 'A';

strcpy(questions[15].question, "Which of the following is a field of study that gives computers the ability to learn without being explicitly programmed?\nA. Machine learning\nB. Database programming\nC. Data mining\nD. Web programming");
questions[15].answer = 'A';

strcpy(questions[16].question, "What is the output of a machine learning algorithm?\nA. A model\nB. A hypothesis\nC. An educated guess\nD. A feature");
questions[16].answer = 'A';

strcpy(questions[17].question, "Which type of machine learning does not receive labeled data?\nA. Unsupervised learning\nB. Semi-supervised learning\nC. Reinforcement learning\nD. Supervised learning");
questions[17].answer = 'A';

strcpy(questions[18].question, "Which of the following is a parameter that is set before the training of a machine learning model?\nA. Hyperparameter\nB. Label\nC. Feature\nD. Instance");
questions[18].answer = 'A';

strcpy(questions[19].question, "Which of the following is a set of data used to tune the hyperparameters of a machine learning model?\nA. Validation set\nB. Training set\nC. Development set\nD. Testing set");
questions[19].answer = 'A';

strcpy(questions[20].question, "Which of the following is NOT a type of deep learning?\nA. Random Forest Logic\nB. Generative Adversarial Network\nC. Recurrent Neural Network\nD. Convolutional Neural Network");
questions[20].answer = 'A';

strcpy(questions[21].question, "Which of the following domains can benefit from deep learning?\nA. All the rest\nB. Medicine\nC. Financial sector\nD. Car industry");
questions[21].answer = 'A';

strcpy(questions[22].question, "Which deep learning technique is best suited for image recognition tasks?\nA. Convolutional Neural Network\nB. Autoencoder\nC. Recurrent Neural Network\nD. Generative Adversarial Network");
questions[22].answer = 'A';

strcpy(questions[23].question, "Which deep learning technique is best suited for language interpretation tasks?\nA. Recurrent Neural Network\nB. Generative Adversarial Network\nC. Convolutional Neural Network\nD. Autoencoder");
questions[23].answer = 'A';

strcpy(questions[24].question, "What does deep learning mean?\nA. A type of machine learning that uses artificial neural networks with multiple layers to learn from data\nB. A type of machine learning that is used only for hard tasks\nC. A type of machine learning that does not use neural networks\nD. A type of machine learning that uses only high volumes of data");
questions[24].answer = 'A';

strcpy(questions[25].question, "Which one is the basic part of an artificial neural network?\nA. Neuron\nB. Layer\nC. Weight\nD. Function");
questions[25].answer = 'A';

strcpy(questions[26].question, "Which one is the layer that receives data to feed the neural network?\nA. Input layer\nB. Output layer\nC. Hidden layer\nD. Outside layer");
questions[26].answer = 'A';

strcpy(questions[27].question, "Which of the following is a type of machine learning that uses artificial neural networks with multiple hidden layers?\nA. Deep learning\nB. Supervised learning\nC. Layer learning\nD. Reinforcement learning");
questions[27].answer = 'A';

strcpy(questions[28].question, "Which of the below is a challenge for deep learning?\nA. Explainability\nB. Cost\nC. Finding data\nD. Finding people who can create the programs");
questions[28].answer = 'A';

strcpy(questions[29].question, "Which of the following is a type of deep learning model?\nA. Convolutional Neural Networks\nB. k-Nearest Neighbors\nC. Support Vector Machine\nD. Logistic Regression");
questions[29].answer = 'A';

strcpy(questions[30].question, "How can we mitigate bias in AI?\nA. use a diverse dataset\nB. use more data\nC. use biased data\nD. use less data");
questions[30].answer = 'A';

strcpy(questions[31].question, "What possible consequences can bias in AI lead to?\nA. discrimination\nB. efficiency\nC. accuracy\nD. transparency");
questions[31].answer = 'A';

strcpy(questions[32].question, "What is the main cause of bias in AI programming?\nA. data bias\nB. human bias\nC. algorithmic bias\nD. judgment bias");
questions[32].answer = 'A';

strcpy(questions[33].question, "Which of the following is NOT an example of algorithmic bias in AI?\nA. A search engine that is more likely to return results for popular websites than for less popular websites.\nB. A spam filter that is more likely to flag emails from women than from men.\nC. A resume screening algorithm that is more likely to recommend male candidates for high-paying jobs than female candidates.\nD. A facial recognition algorithm that is more accurate at identifying white people than black people.");
questions[33].answer = 'A';

strcpy(questions[34].question, "Which can be an option to avoid bias in AI-powered decisions?\nA. have human oversight\nB. don’t use AI to take those decisions\nC. create a separate AI to validate the first one\nD. only use AI for small decisions");
questions[34].answer = 'A';

strcpy(questions[35].question, "Which one is a way to mitigate bias in AI?\nA. Create audit systems for bias\nB. Don’t use the products\nC. Highlight the bias and ignore it\nD. Don’t question the output of the application");
questions[35].answer = 'A';

strcpy(questions[36].question, "What is a possible consequence of bias in AI?\nA. Unfair outcomes\nB. Transparent outcomes\nC. Good enough outcomes\nD. Accurate outcomes");
questions[36].answer = 'A';

strcpy(questions[37].question, "What is a correct definition for bias in AI?\nA. Bias in AI programming can lead to apps that favor a certain group of people or certain result\nB. Bias in AI programming can lead to apps that make mistakes\nC. Bias in AI programming can lead to apps that are inefficient\nD. Bias in AI programming can lead to apps created only for a certain situation");
questions[37].answer = 'A';

strcpy(questions[38].question, "What is a cause of bias in AI?\nA. All the rest\nB. Data used to train the AI is not representative\nC. The AI inherits the bias of the programmers\nD. The AI is too rudimentary to differentiate human nuances");
questions[38].answer = 'A';

strcpy(questions[39].question, "Who is responsible for fighting and mitigating bias in AI programming?\nA. All the rest\nB. The programmers\nC. The private companies\nD. The public sector");
questions[39].answer = 'A';

strcpy(questions[40].question, "Which of the following is a benefit of using AI to protect privacy?\nA. all the rest\nB. AI tools can be used to develop new encryption algorithms\nC. AI tools can be used to identify and remove personally identifiable information\nD. AI tools can be used to discover data breaches");
questions[40].answer = 'A';

strcpy(questions[41].question, "Which of the following is NOT a type of privacy-preserving AI?\nA. Centralized learning\nB. Differential privacy\nC. Federated learning\nD. Secure multi-party computation");
questions[41].answer = 'A';

strcpy(questions[42].question, "What is the most important thing to keep in mind when thinking about privacy in AI?\nA. Before releasing an AI product we need to prioritize the privacy elements\nB. Privacy is not mandatory\nC. Privacy is just a module\nD. Privacy concerns only matter when users complain");
questions[42].answer = 'A';

strcpy(questions[43].question, "Which of the following is a challenge to implementing privacy-preserving AI?\nA. All the rest\nB. Need to educate developers and users\nC. Need to develop new algorithms\nD. Trade-offs between privacy and accuracy");
questions[43].answer = 'A';

strcpy(questions[44].question, "What is the difference between PII and non-PII?\nA. PII identifies individuals, non-PII does not\nB. PII is used by businesses, non-PII by governments\nC. PII is public, non-PII is private\nD. PII is online data, non-PII is offline data");
questions[44].answer = 'A';

strcpy(questions[45].question, "Which of the following is NOT a privacy-preserving AI practice?\nA. Data sharing\nB. Data anonymization\nC. Data minimization\nD. Differential privacy");
questions[45].answer = 'A';

strcpy(questions[46].question, "Which is an example of privacy-preserving AI?\nA. An assistant that responds to natural language\nB. Facial recognition on the street\nC. Recommender system from past purchases\nD. All the other options");
questions[46].answer = 'A';

strcpy(questions[47].question, "Which is NOT a way to address privacy concerns?\nA. Using AI to gather more data\nB. Developing transparent AI\nC. Giving users control over their data\nD. Creating privacy laws");
questions[47].answer = 'A';

strcpy(questions[48].question, "What is a privacy-preserving AI principle?\nA. Using AI to process data to protect individual privacy\nB. Using AI to discriminate\nC. Using AI to collect maximum data\nD. Using AI to decide without consent");
questions[48].answer = 'A';

strcpy(questions[49].question, "What is a risk of AI-powered social media products?\nA. All the rest\nB. Tracking users without consent\nC. Personalized content without knowledge\nD. Deep fakes spreading misinformation");
questions[49].answer = 'A';

strcpy(questions[50].question, "Which is NOT a benefit of transparency in AI ethics?\nA. It makes AI systems more accurate\nB. Helps mitigate ethical risks\nC. Builds trust in AI\nD. Ensures responsible use");
questions[50].answer = 'A';

strcpy(questions[51].question, "Which is NOT a challenge to achieving transparency?\nA. Developers are reluctant to share info\nB. No standard for AI transparency\nC. Complex systems hard to explain\nD. No universal solution");
questions[51].answer = 'A';

strcpy(questions[52].question, "Which is a transparency-enhancing measure?\nA. All other answers\nB. Publish technical documentation\nC. Provide training data access\nD. Develop explainable AI tools");
questions[52].answer = 'A';

strcpy(questions[53].question, "Which is NOT expected from an ethical reviewer?\nA. Approving/rejecting AI for release\nB. Detect transparency issues\nC. Guide AI development\nD. Document transparency process");
questions[53].answer = 'A';

strcpy(questions[54].question, "What promotes transparency in AI ethics?\nA. All other answers\nB. Accountability\nC. Educating users\nD. Creating transparency playbooks");
questions[54].answer = 'A';

strcpy(questions[55].question, "Which is NOT a way to measure transparency?\nA. Public’s understanding of AI\nB. Number of systems reviewed\nC. Published AI ethics papers\nD. Developers’ understanding");
questions[55].answer = 'A';

strcpy(questions[56].question, "Which is NOT a cost of transparency?\nA. Increased trust\nB. Reduced accuracy\nC. Higher development cost\nD. Privacy risks");
questions[56].answer = 'A';

strcpy(questions[57].question, "Which is NOT a way to make AI explainable?\nA. All other answers\nB. Create visualization tools\nC. Use smaller data samples\nD. Use simple algorithms");
questions[57].answer = 'A';

strcpy(questions[58].question, "What is the best way to ensure transparency?\nA. Hybrid: governments, NGOs, and industry together\nB. Top-down by governments\nC. Don’t regulate\nD. Bottom-up by companies");
questions[58].answer = 'A';

strcpy(questions[59].question, "Which is NOT a challenge to transparency?\nA. All the rest\nB. Lack of expertise\nC. Lack of resources\nD. Lack of time");
questions[59].answer = 'A';

strcpy(questions[60].question, "Which of the following is a benefit of using AI to protect privacy?\nA. all the rest\nB. AI tools can be used to develop new encryption algorithms\nC. AI tools can be used to identify and remove personally identifiable information\nD. AI tools can be used to discover data breaches");
questions[60].answer = 'A';

strcpy(questions[61].question, "Which of the following is NOT a type of privacy-preserving AI?\nA. Centralized learning\nB. Differential privacy\nC. Federated learning\nD. Secure multi-party computation");
questions[61].answer = 'A';

strcpy(questions[62].question, "What is the most important thing to keep in mind when thinking about privacy in AI?\nA. Before releasing an AI product we need to prioritize the privacy elements\nB. Privacy is not mandatory\nC. Privacy is just a module\nD. Privacy concerns only matter when users complain");
questions[62].answer = 'A';

strcpy(questions[63].question, "Which of the following is a challenge to implementing privacy-preserving AI?\nA. All the rest\nB. Need to educate developers and users\nC. Need to develop new algorithms\nD. Trade-offs between privacy and accuracy");
questions[63].answer = 'A';

strcpy(questions[64].question, "What is the difference between PII and non-PII?\nA. PII identifies individuals, non-PII does not\nB. PII is used by businesses, non-PII by governments\nC. PII is public, non-PII is private\nD. PII is online data, non-PII is offline data");
questions[64].answer = 'A';

strcpy(questions[65].question, "Which of the following is NOT a privacy-preserving AI practice?\nA. Data sharing\nB. Data anonymization\nC. Data minimization\nD. Differential privacy");
questions[65].answer = 'A';

strcpy(questions[66].question, "Which is an example of privacy-preserving AI?\nA. An assistant that responds to natural language\nB. Facial recognition on the street\nC. Recommender system from past purchases\nD. All the other options");
questions[66].answer = 'A';

strcpy(questions[67].question, "Which is NOT a way to address privacy concerns?\nA. Using AI to gather more data\nB. Developing transparent AI\nC. Giving users control over their data\nD. Creating privacy laws");
questions[67].answer = 'A';

strcpy(questions[68].question, "What is a privacy-preserving AI principle?\nA. Using AI to process data to protect individual privacy\nB. Using AI to discriminate\nC. Using AI to collect maximum data\nD. Using AI to decide without consent");
questions[68].answer = 'A';

strcpy(questions[69].question, "What is a risk of AI-powered social media products?\nA. All the rest\nB. Tracking users without consent\nC. Personalized content without knowledge\nD. Deep fakes spreading misinformation");
questions[69].answer = 'A';


        shuffle_questions();
    }

    int is_question_active() {
        return question_active;
    }

    void trigger_question_if_needed(int px, int py) {
        // Ex: daca pasesti pe o celula 'Q' din harta
        extern char map1[15][21];
            question_active = 1;
            current_q = shuffled_indexes[current_question_index++];
            selected_answer = '\0';
        }
    

    void update_question() {
        if (!question_active) return;
        if (IsKeyPressed(KEY_A)) selected_answer = 'A';
        if (IsKeyPressed(KEY_B)) selected_answer = 'B';
        if (IsKeyPressed(KEY_C)) selected_answer = 'C';
        if (IsKeyPressed(KEY_D)) selected_answer = 'D';

        if (selected_answer != '\0') {
            if (selected_answer == questions[current_q].answer) {
                score += 50;
            } else {
                // scade viata daca ai un sistem de vieti extern
                extern int lives;
                lives--;
                if (lives <= 0) {
                    game_over = true;
                }
            }
            question_active = 0;
            selected_answer = '\0';
        }
    }

    void draw_question() {
        if (!question_active) return;
        DrawRectangle(50, 50, 700, 300, LIGHTGRAY);
        DrawRectangleLines(50, 50, 700, 300, BLACK);

        DrawText(questions[current_q].question, 60, 60, 16, DARKBLUE);
        DrawText("Press A / B / C / D", 60, 280, 20, MAROON);
    }
