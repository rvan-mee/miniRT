/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 19:30:46 by lsinke        #+#    #+#                 */
/*   Updated: 2022/06/30 19:30:46 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNARR_H
# define DYNARR_H

# include <stdbool.h>
# include <stddef.h>

typedef void	(*t_foreach)(void *, void *);

/**
 * A dynamic (growable) array, usable for all types
 * 
 * arr is the internal array
 * elem_size is the length of the data type (sizeof <type>)
 * capacity is the length (in objects!) of the internal array
 * length is the amount of objects currently in the array
 */
typedef struct s_dynarr {
	void			*arr;
	const size_t	elem_size;
	size_t			capacity;
	size_t			length;
}	t_dynarr;

/**
 * Create a new (growable) dynamic array
 * 
 * @param[out] ptr A pointer where the new dynamic array will be created
 * @param[in] init_size The initial length (in objects!) of the internal array
 * @param[in] data_size The length of the data type this array will be used for
 * 
 * @return true if everything went as planned, false if an error occurred
 */
bool	dynarr_create(t_dynarr *ptr, size_t init_size, size_t data_size);

/**
 * Frees all resources used in this array (the internal array)
 * 
 * @param[in/out] arr the dynarr to delete
 */
void	dynarr_delete(t_dynarr *arr);

/**
 * "Finalize" this array. Shrinks the internal array to the minimal length
 * necessary for everything to fit
 * 
 * @param arr[in/out] the buffer to finalize
 * 
 * @return true if everything went as planned, false if an error occurred
 * 
 * This function will not modify (and not free) the array if an error occurs
 */
bool	dynarr_finalize(t_dynarr *arr);

/**
 * Append some objects to the end of this array. Growing the internal array
 * if necessary
 * 
 * @param arr[in/out] the dynarr to append to
 * @param objs[in] the objects to append to the array
 * @param count[in] the amount of objects to be added
 * 
 * @return true if everything went as planned, false if an error occurred
 */
bool	dynarr_add(t_dynarr *arr, const void *objs, size_t count);

/**
 * Append a single object to the end of this array. Growing the internal array
 * if necessary
 *
 * @param arr[in/out] the dynarr to append to
 * @param objs[in] the object to append to the array
 *
 * @return true if everything went as planned, false if an error occurred
 */
bool	dynarr_addone(t_dynarr *arr, const void *obj);

/**
 * Get an object from a certain index in the array.
 * 
 * @param arr[in/out] the dynarr to get the object from
 * @param index[in] the index of the object in the array
 *
 * @return The object at the given index, or NULL if index is out of bounds
 */
void	*dynarr_get(t_dynarr *arr, size_t index);

/**
 * Get a pointer to a certain index in the array. This function does not check
 * if this is an valid index! Use with care!
 *
 * @param arr[in/out] the dynarr to get the object from
 * @param index[in] the index of the object in the array
 *
 * @return The pointer to the given index.
 */
void	*dynarr_get_u(t_dynarr *arr, size_t index);

/**
 * Get a pointer to the object in the highest index in the array.
 * 0
 * @param arr[in/out] the dynarr to get the object from
 * 
 * @return The pointer to the object at the highest index in the array.
 */
void	*dynarr_get_top(t_dynarr *arr);

/**
 * Get a pointer to the last index in the array, and decrease length by one.
 * The data at this address will get overwritten if something else gets added
 * to (same index of) the array!
 * 
 * @param arr[in/out] the dymarr to pop the object from
 * 
 * @return The pointer to the object that was popped, or NULL if length is 0
 */
void	*dynarr_pop(t_dynarr *arr);

/**
 * Store an object at a certain index in the array. Growing the array to that
 * length if necessary.
 * 
 * @param arr[in/out] the dynarr to store the object in 
 * @param index[in] the index where the object will be stored in the array
 * @param obj[in] the object to store
 * 
 * @return true if everything went as planned, false if an error occurred 
 */
bool	dynarr_set(t_dynarr *arr, size_t index, const void *obj);

/**
 * Grow (or shrink) the internal array
 * 
 * @param arr[in/out] the dynarr to grow
 * @param new_size[in] the new length (in objects!) to grow the array to.
 * 
 * @return true if everything went as planned, false if an error occurred
 */
bool	dynarr_grow(t_dynarr *arr, size_t new_size);

/**
 * Perform a function on every object in this dynarr
 *
 * @param arr[in/out] the dynarr to iterate over 
 * @param f[in] the function to call with every object
 * @param param[in] an extra parameter for the function to be called
 */
void	dynarr_foreach(t_dynarr *arr, void (*f)(void *, void *), void *param);

#endif //DYNARR_H
