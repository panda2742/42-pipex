/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:11:30 by ehosta            #+#    #+#             */
/*   Updated: 2024/12/16 18:11:30 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static int	_dispatch_putnbr(int base_id, long double value);
static int	_parse_flag(char *flag_ptr, va_list args);
static int	_is_valid_flag_name(char flag_name, char *valid_flags);
static int	_parse_format(char *str, va_list args);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		return_value;

	if (!format || !*format)
		return (-1);
	va_start(args, format);
	return_value = _parse_format((char *)format, args);
	va_end(args);
	return (return_value);
}

static int	_dispatch_putnbr(int base_id, long double value)
{
	if (base_id == 0)
		return (ft_putnbr_base_fd(value, "0123456789", PRINTF_FD));
	if (base_id == 1)
		return (ft_putnbr_base_fd(value, "0123456789abcdef", PRINTF_FD));
	if (base_id == 2)
		return (ft_putnbr_base_fd(value, "0123456789ABCDEF", PRINTF_FD));
	return (-1);
}

static int	_parse_flag(char *flag_ptr, va_list args)
{
	char	flag_name;

	flag_name = *(flag_ptr + 1);
	if (flag_name == '%')
		return (ft_putchar_fd('%', PRINTF_FD));
	if (flag_name == 'c')
		return (ft_putchar_fd(va_arg(args, int), PRINTF_FD));
	if (flag_name == 's')
		return (ft_putstr_fd(va_arg(args, char *), PRINTF_FD));
	if (flag_name == 'd' || flag_name == 'i')
		return (_dispatch_putnbr(0, (long long)va_arg(args, int)));
	if (flag_name == 'u')
		return (_dispatch_putnbr(0, (unsigned int)va_arg(args, unsigned int)));
	if (flag_name == 'x')
		return (_dispatch_putnbr(1, (unsigned int)va_arg(args, unsigned int)));
	if (flag_name == 'X')
		return (_dispatch_putnbr(2, (unsigned int)va_arg(args, unsigned int)));
	if (flag_name == 'p')
		return (ft_putptr_fd(
				(unsigned long long)va_arg(args, void *), PRINTF_FD)
		);
	return (0);
}

static int	_is_valid_flag_name(char flag_name, char *valid_flags)
{
	int		i;

	if (!flag_name)
		return (0);
	i = 0;
	while (i < 10)
	{
		if (valid_flags[i] == flag_name)
			return (1);
		i++;
	}
	return (0);
}

static int	_parse_format(char *str, va_list args)
{
	int	printed_chars;
	int	print_result;
	int	i;

	printed_chars = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && _is_valid_flag_name(str[i + 1], "csdiuxXp%"))
		{
			print_result = _parse_flag(&str[i], args);
			if (print_result == -1)
				return (-1);
			printed_chars += print_result;
			i += 2;
			continue ;
		}
		print_result = ft_putchar_fd(str[i], PRINTF_FD);
		if (print_result == -1)
			return (-1);
		printed_chars++;
		i++;
	}
	return (printed_chars);
}
