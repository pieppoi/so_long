/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 00:00:00 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/26 00:00:00 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	const char	*it;

	if (s == NULL)
		return (0);
	it = s;
	while (*it)
		it++;
	return ((size_t)(it - s));
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	dup = (char *)malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (src == NULL)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dlen >= dstsize)
		return (dstsize + slen);
	i = 0;
	while (dlen + i + 1 < dstsize && src[i] != '\0')
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	if (s == NULL)
		return (NULL);
	ch = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if (size != 0 && count > ((size_t)-1) / size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

static size_t	count_words(const char *s, char sep)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (s && *s)
	{
		if (*s != sep && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == sep)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static char	*substr_dup(const char *start, size_t len)
{
	char	*str;

	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, start, len + 1);
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char		**out;
	size_t		i;
	size_t		wcount;
	const char	*start;
	const char	*it;

	if (s == NULL)
		return (NULL);
	wcount = count_words(s, c);
	out = (char **)ft_calloc(wcount + 1, sizeof(char *));
	if (out == NULL)
		return (NULL);
	i = 0;
	it = s;
	while (*it)
	{
		while (*it == c)
			it++;
		if (*it == '\0')
			break ;
		start = it;
		while (*it && *it != c)
			it++;
		out[i] = substr_dup(start, (size_t)(it - start));
		if (out[i] == NULL)
			return (out);
		i++;
	}
	out[i] = NULL;
	return (out);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	if (needle == NULL || haystack == NULL)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i + needle_len <= len)
	{
		j = 0;
		while (j < needle_len && haystack[i + j] == needle[j])
			j++;
		if (j == needle_len)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

