#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>


#define H_STR_MAX 4

/* malloc family allocation macros */
#define CALLOC(type)             ((type*) calloc(1, sizeof(type)))
#define CALLOC_VOID(nmemb, size) ((void*) calloc(nmemb, size))
#define CALLOC_ARRAY(type, num)  ((type*) calloc(num, sizeof(type)))

/* what a room is */
typedef struct room_info {
    char *room_name;
    bool pub_flag;       // is this room public or not?
    char *password;      // if not public. Otherwise dont allocate
    char **room_users;   // Reallocates in chunks.
    uint32_t num_users;
    size_t max_name_len; // Given in init
    char **history;      // Ring buffer of room history
    int hist_start;
    int hist_end;
} struct_room_info;

struct_room_info* _room_init_info(bool pub, char *pw)
{
    struct_room_info *init;
    size_t len;

    if (pub == false && pw == NULL) {
        return NULL;
    }

    init = CALLOC(struct_room_info);
    if (!init) {
        return NULL;
    }

    /* set password if room is private, maybe do this outside of funct? */
    if (pub == false) {
        len = strlen(pw) + 1;
        init->password = CALLOC_ARRAY(char, len);
        if (!init->password) {
            return NULL;
        }

        strncpy(init->password, pw, len);
        init->pub_flag = pub;
    } else {
        init->pub_flag = true;
    }

    /* TODO: basically static. Not enough time for proper data structures  D: */
    init->room_users = CALLOC_ARRAY(char*, 10);
    if (!init->room_users) {
        return NULL;
    }
    /* individual index ponters not filled. allocate when name is passed. */


    /* note history is a ring buffer, felt it okay to allocate it all here
     * for now.
     *
     * Allocate entire ring buffer, without its members
     */
    init->history = CALLOC_ARRAY(char*, H_STR_MAX);
    if (!init->history) {
        return NULL;
    }

    init->max_name_len = 25;
    init->hist_start = H_STR_MAX-1;
    init->hist_end = 0;

    return init;
} /* end _room_init_info() */



int room_add_history(struct_room_info *room, char *room_name, char *msg)
{
    int len;

    /* add new message to end of the list */
    len = strlen(msg) + 1;
    printf("pre_if_statement: start: %d, end %d\n", room->hist_start, room->hist_end);
    if (room->history[room->hist_end] != NULL) {
        free(room->history[room->hist_end]);
        room->history[room->hist_end] = NULL;

	printf("hist_start_pre: %d\n", room->hist_start);
        room->hist_start = (room->hist_start + 1) % H_STR_MAX;
	printf("hist_start_after: %d\n", room->hist_start);
    }

    /* allocate to appropriate size */
    room->history[room->hist_end] = CALLOC_ARRAY(char, len);

    strncpy(room->history[room->hist_end], msg, len);

    /* increment pointer ring */
    printf("hist_end_pre: %d\n", room->hist_end);
    room->hist_end = (room->hist_end + 1) % H_STR_MAX;
    printf("hist_end_after: %d\n", room->hist_end);

    return 0;
} /* end room_add_history */



int main(void)
{
	struct_room_info *room_info =  _room_init_info(true, NULL);

	room_add_history(room_info, "my_room", "fuck yawah");
	room_add_history(room_info, "my_room", "fuck nahway");
	room_add_history(room_info, "my_room", "why do dumb shit hate science");
	room_add_history(room_info, "my_room", "etetra.");
	room_add_history(room_info, "my_room", "fuck yawah");
	room_add_history(room_info, "my_room", "fuck yawah");
	room_add_history(room_info, "my_room", "fuck yawah");
	room_add_history(room_info, "my_room", "fuck yawah");

	return 0;
}
