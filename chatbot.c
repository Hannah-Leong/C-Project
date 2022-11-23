/*
 * INF1002 (C Language) Group Project.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#include <stdio.h>
#include <string.h>
#include "chat1002.h"


/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return "Chatbot";

}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "User";

}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {

	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}

	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {

	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;

}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {

	snprintf(response, n, "Goodbye!");

	return 1;

}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {

	if (strcmp(intent, "load") == 0) {
        return 1;
    }
	return 0;

}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {
  
  char filename[MAX_INPUT]; // declare array filename
  int count; // declare count

  // if number of words of input < 2, user only input 'load' 
  if (inc < 2){
    snprintf(response, n, "Please enter a file name.\n");
    return 0;
  }

  // if second element of input not equals to null, it will be copied as filename
  if (inv[1] != NULL) {
      strcpy(filename, inv[1]);
      count = knowledge_read((FILE *) filename); // read the contents of the file
      snprintf(response, n, "Read %d responses from %s.", count, filename);
  } else {
    snprintf(response, n, "Sorry, could not open that file.");
  }

  return 0;

}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {

	/* to be implemented */

	if (compare_token(intent, "what") == 0 || compare_token(intent, "where") == 0 || compare_token(intent, "who") == 0) {
		return 1;
	}
	return 0;

}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {
    /* To be implemented */

    char *after_question_words[] = {"is", "are"};
    char entity[MAX_RESPONSE] = "";
    int loop = 0;
    int entityPos = 1;
    //Ignore the words in after_question_words, which can vary based on the existance of the word.
    while (loop < 2) {
        //Compare if they exist. If they do, then entity is in inv[2] onwards.
        if (compare_token(inv[1], after_question_words[loop]) == 0) {
            entityPos += 1;
        }
        loop++;
    }
    //Get the entity.
    for (int i = entityPos; i < inc; i++) {
        strcat(entity, inv[i]);
        if (i != inc - 1) {
            strcat(entity, " ");
        }

    }
    if (knowledge_get(inv[0], entity, response, n)) {
        prompt_user(response, n, "I don't know. %s is %s?", inv[0], entity);
        if (knowledge_put(inv[0], entity, response) == 0) {
            //Change the buffer to thank the user rather than displaying his inputs.
            snprintf(response, n, "Thank you.");
        } else {
            snprintf(response, n, ":-(");
        }
    }
    return 0;

}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent){
  
  if (compare_token(intent, "reset") == 0) {
        return 1;
    }
	return 0;
  
}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n){ 
  knowledge_reset();
  snprintf(response, MAX_RESPONSE, "Chatbot reset.");
	return 0;
  
}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {

	if (compare_token(intent, "save") == 0) {
        return 1;
    }

	return 0;

}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {

  FILE *to_save_file; // declare pointer to a FILE
  char filename[MAX_INPUT]; // declare the file name

  // if input is the form of save as or save to, third element of input will be copied as filename
  if (compare_token(inv[1], "as") == 0 || compare_token(inv[1], "to") == 0) {
      strcpy(filename, inv[2]);
  // else, input is just save (name), second element of input will be copied as filename
  } else {
      strcpy(filename, inv[1]);
  }

  // open file with w mode (creating an empty file for writing)
  to_save_file = fopen(filename, "w");
  if (to_save_file == NULL) {
    snprintf(response, n, "Could not open file.\n");
    return 1;
  }

  // write to file
  knowledge_write(to_save_file);

  // close the file
  fclose(to_save_file);
  snprintf(response, n, "My knowledge has been saved to %s.", filename);
  
  return 0;
  
}



