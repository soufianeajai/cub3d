
#include"../cub3d.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_signe(const char **str)
{
	int	signe;

	signe = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			signe = -signe;
		(*str)++;
	}
	return (signe);
}

double	atoi_double(const char *str)
{
	double	nbr;
	int		signe;
	double	nbr_f;
	int		len_f;

	signe = ft_signe(&str);
	nbr = 0;
	nbr_f = 0;
	len_f = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (*str - '0') + (10 * nbr);
		str++;
	}
	if (*str == '.')
		str++;
	len_f = ft_strlen(str);
	while (*str >= '0' && *str <= '9')
	{
		nbr_f = (*str - '0') + (10 * nbr_f);
		str++;
	}
	nbr_f = nbr_f * (pow(10, -len_f));
	return (signe * (nbr + nbr_f));
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			pos;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	pos = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (pos < n)
	{
		if (str1[pos] != str2[pos])
			return (str1[pos] - str2[pos]);
		pos++;
	}
	return (0);
}

void	free_ptr(void *ptr)
{
	free (ptr);
	ptr = 0;
}
