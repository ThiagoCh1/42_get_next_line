/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thribeir <thribeir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:27:37 by thribeir          #+#    #+#             */
/*   Updated: 2025/09/13 14:28:52 by thribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

char	*gnl_strchr(const char *str, int c)
{
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	j = 0;
	dest_len = 0;
	src_len = 0;
	while (dest_len < size && dest[dest_len] != '\0')
		dest_len++;
	while (src[src_len])
		src_len++;
	if (dest_len >= size)
		return (dest_len + src_len);
	i = dest_len;
	while (i < size - 1 && src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char const *s2)
{
	char	*dest;
	char	*orig_s1;
	size_t	len;

	orig_s1 = s1;
	if (s1 == NULL)
		s1 = "";
	len = gnl_strlen(s1) + gnl_strlen(s2) + 1;
	dest = malloc(len);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, len);
	ft_strlcat(dest, s2, len);
	if (orig_s1 != NULL)
		free(orig_s1);
	return (dest);
}
