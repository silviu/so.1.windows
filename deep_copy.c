#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "parser.h"
#define strdup			_strdup


static word_t* word_t_copy(word_t* word)
{
	word_t* new_word;
	if (word == NULL)
		return NULL;

	new_word = calloc(sizeof(word_t), 1);

	if (word->string)
		new_word->string = strdup(word->string);

	new_word->expand = word->expand;
	
	new_word->next_part = word_t_copy(word->next_part);
	new_word->next_word = word_t_copy(word->next_word);

	return new_word;
}

static simple_command_t* scmd_deep_copy(simple_command_t* scmd)
{
	simple_command_t* new_scmd = calloc(sizeof(simple_command_t), 1);

	new_scmd->verb = word_t_copy(scmd->verb);
	new_scmd->params = word_t_copy(scmd->params);
	new_scmd->in = word_t_copy(scmd->in);
	new_scmd->out = word_t_copy(scmd->out);
	new_scmd->err = word_t_copy(scmd->err);

	new_scmd->io_flags = scmd->io_flags;

	return new_scmd;
}

command_t* command_deep_copy(command_t* root)
{
	command_t* new_root = calloc(sizeof(command_t), 1);
	new_root->op = root->op;

	if (root->op == OP_NONE)
		new_root->scmd = scmd_deep_copy(root->scmd);
	else {
		new_root->cmd1 = command_deep_copy(root->cmd1);
		new_root->cmd2 = command_deep_copy(root->cmd2);
	}
	return new_root;
}

static void free_word_t(word_t* word)
{
	if (word == NULL)
		return;

	if (word->string)
		free((char*)word->string);

	if (word->next_part)
		free_word_t(word->next_part);

	if (word->next_word)
		free_word_t(word->next_word);

	free(word);
}

static void free_scmd(simple_command_t* scmd)
{
	free_word_t(scmd->verb);
	free_word_t(scmd->params);
	free_word_t(scmd->in);
	free_word_t(scmd->out);
	free_word_t(scmd->err);
	free(scmd);
}

void command_deep_free(command_t* root)
{
	if (root->op == OP_NONE)
		free_scmd(root->scmd);
	else {
		command_deep_free(root->cmd1);
		command_deep_free(root->cmd2);
	}
	free(root);
}
