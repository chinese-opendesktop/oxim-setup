#ifndef _PHRASE_RECORD
#define _PHRASE_RECORD

typedef gchar* phrases_t[100][2];
void phrase_reload( phrases_t* ret_phrases ,gint* ret_size);
void phrase_update( phrases_t phrases, gint size);

#endif //_PHRASE_RECORD
