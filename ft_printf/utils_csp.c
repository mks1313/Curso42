/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_csp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:15:22 by mmarinov          #+#    #+#             */
/*   Updated: 2024/08/03 17:55:59 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *s)
{
	if (s == 0)
		s = "null";
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	ft_ptrlen(unsigned long long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 16;
		len++;
	}
	return (len);
}

void	ft_putnum_hex(unsigned long num)
{
	char	*hex_digits;
	char	buffer[16];
	int		i;

	hex_digits = "0123456789abcdef";
	i = 0;
	if (num == 0)
	{
		write(1, "0", 1);
		return ;
	}
	while (num != 0)
	{
		buffer[i++] = hex_digits[num % 16];
		num /= 16;
	}
	while (i--)
		write(1, &buffer[i], 1);
}

int	ft_print_ptr(void *p)
{
	unsigned long	addr;
	int				printed_nums;

	printed_nums = 0;
	addr = (unsigned long)p;
	write(1, "0x", 2);
	printed_nums += 2;
	if (addr == 0)
	{
		printed_nums += ft_print_str("(nil)");
		return (printed_nums);
	}
	else
	{
		ft_putnum_hex(addr);
		printed_nums += ft_ptrlen(addr);
	}
	return (printed_nums);
}