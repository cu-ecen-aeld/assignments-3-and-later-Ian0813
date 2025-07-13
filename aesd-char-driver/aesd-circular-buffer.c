/**
 * @file aesd-circular-buffer.c
 * @brief Functions and data related to a circular buffer imlementation
 *
 * @author Dan Walkes
 * @date 2020-03-01
 * @copyright Copyright (c) 2020
 *
 */

#ifdef __KERNEL__
#include <linux/string.h>
#else
#include <string.h>
#endif

#include <stdio.h>
#include "aesd-circular-buffer.h"

/**
 * @param buffer the buffer to search for corresponding offset.  Any necessary locking must be performed by caller.
 * @param char_offset the position to search for in the buffer list, describing the zero referenced
 *      character index if all buffer strings were concatenated end to end
 * @param entry_offset_byte_rtn is a pointer specifying a location to store the byte of the returned aesd_buffer_entry
 *      buffptr member corresponding to char_offset.  This value is only set when a matching char_offset is found
 *      in aesd_buffer.
 * @return the struct aesd_buffer_entry structure representing the position described by char_offset, or
 * NULL if this position is not available in the buffer (not enough data is written).
 */
struct aesd_buffer_entry *aesd_circular_buffer_find_entry_offset_for_fpos(struct aesd_circular_buffer *buffer,
            size_t char_offset, size_t *entry_offset_byte_rtn )
{
    /**
    * TODO: implement per description
    */
    int offset = 0, block_length = 0, index = 0;
    struct aesd_buffer_entry *target_ptr = NULL;

    if (buffer->full) {
        block_length = AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED;
    } else {
        block_length = GET_BLOCKS_LENGTH(buffer);
    }

    AESD_DEBUG_MSG(stdout, "\n\n[%s] blocks length: %d\n", __func__, block_length);

    while (offset < block_length) {

        AESD_DEBUG_MSG(stdout, "Loop....., block_length: %d, position: %d\n", block_length, buffer->out_offs+offset);
        index = (buffer->out_offs+offset) % AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED;

        if (char_offset >= buffer->entry[index].size) {
            AESD_DEBUG_MSG(stdout, "%s", buffer->entry[index].buffptr);
            AESD_DEBUG_MSG(stdout, "char_offset: %ld\n\n", char_offset);
            char_offset -= (buffer->entry[index].size);
        } else {
            AESD_DEBUG_MSG(stdout, "Break, char_offset: %ld", char_offset);
            break;
        }
        offset++;
    }

    if (offset < block_length) {
        *entry_offset_byte_rtn = char_offset;
        target_ptr = &buffer->entry[index];
    } else {
        printf("No available data.\n");
    }

    return target_ptr;
}

/**
* Adds entry @param add_entry to @param buffer in the location specified in buffer->in_offs.
* If the buffer was already full, overwrites the oldest entry and advances buffer->out_offs to the
* new start location.
* Any necessary locking must be handled by the caller
* Any memory referenced in @param add_entry must be allocated by and/or must have a lifetime managed by the caller.
*/
void aesd_circular_buffer_add_entry(struct aesd_circular_buffer *buffer, const struct aesd_buffer_entry *add_entry)
{
    /**
    * TODO: implement per description
    */

    AESD_DEBUG_MSG(stdout, "\nEnter [%s] out: %d, in: %d\n", __func__, buffer->out_offs, buffer->in_offs);

    if (!buffer->full) {
        buffer->full = ((buffer->in_offs+1)%AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED) == buffer->out_offs ? 1 : 0;
    } else {
        buffer->out_offs = (buffer->out_offs+1)%AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED;
    }

    memcpy(&buffer->entry[buffer->in_offs], add_entry, sizeof(struct aesd_buffer_entry));
    buffer->in_offs = (buffer->in_offs+1)%AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED;

    AESD_DEBUG_MSG(stdout, "\nExit [%s] out: %d, in: %d, full: %d\n", __func__, buffer->out_offs, buffer->in_offs, buffer->full);

    return;
}

/**
* Initializes the circular buffer described by @param buffer to an empty struct
*/
void aesd_circular_buffer_init(struct aesd_circular_buffer *buffer)
{
    memset(buffer,0,sizeof(struct aesd_circular_buffer));
}
