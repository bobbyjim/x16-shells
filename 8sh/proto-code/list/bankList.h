#ifndef _BANK_LIST_H_
#define _BANK_LIST_H_

/*
     Key:Value map implementation using a simple list structure.
 */
 typedef struct {

     int location : 13;  // inside bank (13 bits = 8192 bytes)
     int bank     : 3;   // eight banks, max 64K RAM.

 } BANKED_HASHMAP_POINTER;


 /*
     RAM Bank memory is divided into segments.  Key:value pairs are
     segment-aligned.  This allows me to store header data at predictable
     locations without the need for a true table.
  */
#define     SEGMENT_LENGTH_MINUS_ONE    15
#define     SEGMENTS_PER_BANK           (8192/(SEGMENT_LENGTH_MINUS_ONE+1))

typedef struct {

    char header;
    char data[SEGMENT_LENGTH_MINUS_ONE];

} BANK_LIST_SEGMENT;

BANK_LIST_SEGMENT* bank_list[SEGMENTS_PER_BANK];

/*
     Keys are 1-31 characters in length.
     Values may be 0-255 characters in length.
 */

/*
     If a block's header is 0, then it's unallocated.
     If a block's header is 1-31, then this is a new pair with the key's length indicated.
     If a block's header is 32-127 or 160-255, then it's part of the previous pair's value.
 */

#endif
