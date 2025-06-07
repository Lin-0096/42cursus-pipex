/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:45:30 by linliu            #+#    #+#             */
/*   Updated: 2025/04/24 14:39:27 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <bsd/string.h>
#include <ctype.h>
#include <string.h>


char test_func(unsigned int i, char c)
{
    if (i % 2 == 0)
    {
        if (c >= 'a' && c <= 'z') return (c - 32);
    }
    else
    {
        if (c >= 'A' && c <= 'Z') return (c + 32);
    }
    return c;
}

void test_func1(unsigned int i, char *c)
{
	if (i % 2 == 0 && (*c >= 'a' && *c <= 'z'))
		*c = *c - 32;
}

int	main(void)
{
	printf("isalpha fake:%d\n", ft_isalpha(52));
	printf("real:%d\n", isalpha(52));
	printf("fake:%d\n", ft_isalpha('!'));
	printf("real:%d\n", isalpha('!'));
	printf("------------------------------------------------------------------------------------\n");

	printf("isdigit fake:%i\n", ft_isdigit(48));
	printf("real:%i\n", isdigit(48));
	printf("fake:%i\n", ft_isdigit('!'));
	printf("real:%i\n", isdigit('!'));
	printf("------------------------------------------------------------------------------------\n");
	
	printf("isalnum fake:%d\n", ft_isalnum(50));
	printf("real:%d\n", isalnum(50));
	printf("fake:%d\n", ft_isalnum('!'));
	printf("real:%d\n", isalnum('!'));
	printf("fake:%d\n", ft_isalnum('5'));
	printf("real:%d\n", isalnum('5'));
	printf("------------------------------------------------------------------------------------\n");

	printf("isascii fake: %d\n", ft_isascii('!'));
	printf("real:%d\n", isascii('!'));
	printf("fake:%d\n", ft_isascii(-1));
	printf("real:%d\n", isascii(-1));
	printf("fake:%d\n", ft_isascii(127));
	printf("real:%d\n", isascii(127));
	printf("------------------------------------------------------------------------------------\n");

	printf("ft_isprint fake:%d\n", ft_isprint('~'));
	printf("isprint:%d\n", isprint('~'));
	printf("fake:%d\n", ft_isprint(' '));
	printf("real:%d\n", isprint(' '));
	printf("------------------------------------------------------------------------------------\n");
	
	printf("strlen:fake:%ld\n", ft_strlen("hello"));
	printf("real:%ld\n", strlen("hello"));
	printf("fake:%ld\n", ft_strlen(""));
	printf("real:%ld\n", strlen(""));
	printf("------------------------------------------------------------------------------------\n");
	
	char str1[20] = "hello world";
	char str2[20] = "hello world";
	ft_memset(str1, 'Z', 4);
	memset(str2, 'Z', 4);
	printf("String after ft_memset(): %s\n", str1);
	printf("String after memset(): %s\n", str2);
	printf("------------------------------------------------------------------------------------\n");

	char bzerostr1[20] = "hello world";
	char bzerostr2[20] = "hello world";
	ft_bzero(bzerostr1,4);
	bzero(bzerostr2,4);
	printf("String after ft_bzero():%s\n", str1 + 4);
	printf("String after bzero():%s\n", str2 + 4);
	printf("------------------------------------------------------------------------------------\n");
	
	char memcopydst1[20];
	char memcopydst2[20];
	char memcopysrc[20] = "hello world";
	ft_memcpy(memcopydst1, memcopysrc, 5);
	memcpy(memcopydst2, memcopysrc, 5);
	printf("ft_memcpy:%s\n", memcopydst1);
	printf("memcpy:%s\n", memcopydst2);
	printf("------------------------------------------------------------------------------------\n");
	
	char str[20] = "helloworld";
	ft_memmove(str+2, str, 3);
	printf("ft_memmove:%s\n", str);
	memmove(str+2, str, 3);
	printf("memmove:%s\n", str);

	char buffer1[50] = {0};
	char buffer2[50] = {0};
	char memmove_str[] = "Hello world! Memmove test string";
	memmove(buffer1, memmove_str, 7);
	ft_memmove(buffer2, memmove_str, 7);
	printf("ft_memmove:%s\n", buffer2);
	printf("memmove:%s\n", buffer1);
	printf("------------------------------------------------------------------------------------\n");
	
	char ft_strlcpydst1[6];
	char ft_strlcpysrc1[] = "abcdefg";
	size_t fake_len = ft_strlcpy(ft_strlcpydst1, ft_strlcpysrc1, 6);
	printf("ft_strlcpy string: %s\n",ft_strlcpydst1);
	printf("ft_strlcpy:%zu\n", fake_len);
	
	char ft_strlcpydst2[6];
	char ft_strlcpysrc2[] = "abcdefg";
	size_t real_len = strlcpy(ft_strlcpydst2, ft_strlcpysrc2, 6);
	printf("real strlcpy string:%s\n",ft_strlcpydst2);
	printf("real strlcpy:%zu\n", real_len);
	printf("------------------------------------------------------------------------------------\n");
	
	size_t size = 7;
	char dst1[7] = "hello";
	char dst2[7] = "hello";
	char src[] = "world";
	printf("ft_strlcat:%zu\n", ft_strlcat(dst1, src, size));
	printf("strlcat:%zu\n", strlcat(dst2, src, size));
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_toupper: %d\n", ft_toupper('a'));
	printf("toupper:%d\n", toupper('a'));
	printf("ft_toupper:%d\n", ft_toupper('a' - 1));
	printf("toupper:%d\n", ft_toupper('a' - 1));
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_tolower:%d\n", ft_tolower('A'));
	printf("tolower:%d\n", tolower('A'));
	printf("ft_tolower:%d\n", ft_tolower('A'-1));
	printf("tolower:%d\n", ft_tolower('A'-1));
	printf("------------------------------------------------------------------------------------\n");
	
	const char s[] = "hello,world";
	
	printf("ft_strchr:%s\n", ft_strchr(s, 'l'));
	printf("strchr:%s\n", strchr(s, 'l'));
	printf("ft_strchr:%s\n", ft_strchr(s, 'a'));
	printf("strchr:%s\n", strchr(s, 'a'));
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_strrchr:%s\n", ft_strrchr("abcdef", 'a'));
	printf("strrchr:%s\n", strrchr("abcdef", 'a'));
	printf("ft_strrchr:%s\n", ft_strrchr("abcdef", 'h'));
	printf("strrchr:%s\n", strrchr("abcdef", 'h'));
	printf("------------------------------------------------------------------------------------\n");
	
	const char s1[] = "hello";
	const char s2[] = "hellop";
	printf("ft_strncmp:%d\n", ft_strncmp(s1, s2, 2));
	printf("strncmp:%d\n", strncmp(s1, s2, 2));
	printf("ft_strncmp:%d\n", ft_strncmp(s1, s2, 6));
	printf("strncmp:%d\n", strncmp(s1, s2, 6));
	printf("------------------------------------------------------------------------------------\n");

	printf("ft_memchr:%p\n", ft_memchr("world",'r',4));
	printf("memchr:%p\n", memchr("world",'r',4));
	printf("ft_memchr:%p\n", ft_memchr("world",'o',4));
	printf("memchr:%p\n", memchr("world",'o',4));
	printf("ft_memchr:%p\n", ft_memchr("world",'o',6));
	printf("memchr:%p\n", memchr("world",'o',6));
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_memcmp:%d\n", ft_memcmp("hello", "hello", 5));
	printf("memcmp:%d\n", memcmp("hello", "hello", 5));
	printf("ft_memcmp:%d\n", ft_memcmp("banana", "anana", 10));
	printf("memcmp:%d\n", memcmp("banana", "anana", 10));
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_strnstr:%s\n", ft_strnstr("helloworld", "lowo", 6));
	printf("strnstr:%s\n", strnstr("helloworld", "lowo", 6));
	
	printf("ft_strnstr:%s\n", ft_strnstr("helloworld", "",6));
	printf("strnstr:%s\n", strnstr("helloworld", "", 6));

	printf("ft_strnstr:%s\n", ft_strnstr("helloworld", "hive", 6));
	printf("strnstr:%s\n", strnstr("helloworld", "hive", 6));
	printf("------------------------------------------------------------------------------------\n");

	printf("ft_atoi:%d\n", ft_atoi("-234"));
	printf("atoi:%d\n", atoi("-234"));
	printf("ft_atoi:%d\n", ft_atoi("-+234"));
	printf("atoi:%d\n", atoi("-+234"));
	printf("------------------------------------------------------------------------------------\n");

	printf("ft_calloc:%p\n", ft_calloc(2, 3));
	printf("calloc:%p\n", calloc(2, 3));
	printf("------------------------------------------------------------------------------------\n");

	char	*strdup_src = "String to duplicate";
	char	*res1 = "aaa", *res2 = "aaa";
	printf("before:%s | %s\n", res1, res2);
	res1 = ft_strdup(strdup_src);
	res2 = strdup(strdup_src);
	printf("after ft_strdup:%s\n", res1);
	printf("after strdup:%s\n", res2);
	free(res1);
	free(res2);
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_substr:%s\n", ft_substr("hello", 2, 3));
	printf("ft_substr:%s\n", ft_substr("Hello world! Find a substring", 15, 8));
	printf("ft_substr:%s\n", ft_substr("Hello world! Find a substring", 50, 50));
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_strjoin:%s\n", ft_strjoin("", "world"));
	printf("ft_strjoin:%s\n", ft_strjoin("hello", ""));
	printf("ft_strjoin:%s\n", ft_strjoin("hello", "world"));
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_strtrim:%s\n", ft_strtrim("hello", "llo"));	
	printf("ft_strtrim:%s\n", ft_strtrim("helloll", "ll"));
	printf("ft_strtrim:%s\n", ft_strtrim("ohelloh", "oh"));
	printf("ft_strtrim:%s\n", ft_strtrim("ohelloh", "ho"));
	printf("ft_strtrim:%s\n", ft_strtrim("ohelloh", ""));
	printf("ft_strtrim:%s\n", ft_strtrim("-----------", "-"));
	printf("------------------------------------------------------------------------------------\n");
	
	int i = 0;
	char **arr = ft_split("hello",'l');
	while (arr[i])
	{
		printf("ft_split[i]:%s\n", arr[i]);
		free(arr[i]);
		i++;
	}
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_itoa:%s\n", ft_itoa(2147483647));
	printf("ft_itoa:%s\n", ft_itoa(-2147483648));
	printf("ft_itoa:%s\n", ft_itoa(1234));
	printf("ft_itoa:%s\n", ft_itoa(-1234));
	printf("ft_itoa:%s\n", ft_itoa(0));
	printf("------------------------------------------------------------------------------------\n");
	
	char	*input = "abcdefghijklmnopqrstuvwxyz";
	printf("input:%s\n", input);
	printf("ft_strmapi:%s\n", ft_strmapi(input, test_func));
	printf("------------------------------------------------------------------------------------\n");

	char	input1[] = "zyxwvutsrqponmlkjihgfedcba";
	printf("input:%s\n", input1);
	ft_striteri(input1, test_func1);
	printf("ft_striteri:%s\n", input1);
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_putchar_fd('A', 1):\n");
	ft_putchar_fd('A', 1);
	printf("ft_putchar_fd('+', 1):\n");
	ft_putchar_fd('+', 1);
	printf("\n------------------------------------------------------------------------------------\n");

	printf("ft_putstr_fd('Hello', 1):\n");
	ft_putstr_fd("Hello", 1);
	printf("ft_putstr_fd('Testing ft_putstr', 1):\n");
	ft_putstr_fd("Testing ft_putstr", 1);
	printf("\n------------------------------------------------------------------------------------\n");
	
	printf("ft_putendl_fd('Hello', 1):\n");
	ft_putendl_fd("Hello", 1);
	printf("\nft_putendl_fd('Test123', 1):\n");
	ft_putendl_fd("Test123", 1);
	printf("------------------------------------------------------------------------------------\n");
	
	printf("ft_putnbr_fd(123456, 1):\n");
	ft_putnbr_fd(123456, 1);
	printf("\nft_putnbr_fd(999999999, 1):\n");
	ft_putnbr_fd(999999999, 1);
	printf("\n");
	return 0;
}
