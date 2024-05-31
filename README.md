<p align="center">
	<img width="130px;" src="https://game.42sp.org.br/static/assets/images/42_logo_black.svg" align="center" alt="42" />&nbsp;&nbsp;&nbsp;
	<img width="130px" src="https://game.42sp.org.br/static/assets/achievements/ft_printfm.png" align="center" alt="ft_printf" />
	<h1 align="center">ft_printf</h1>
</p>
<p align="center">
	<img src="https://img.shields.io/badge/Success-107/100_✓-gray.svg?colorA=61c265&colorB=4CAF50&style=for-the-badge">
	<img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black">
	<img src="https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=apple&logoColor=white">
</p>

<p align="center">
	<b><i>Development repository for the 42cursus ft_printf project @ 42 São Paulo</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/iwillenshofer/ft_printf?color=blueviolet" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/iwillenshofer/ft_printf?color=blue" />
	<img alt="GitHub top language" src="https://img.shields.io/github/commit-activity/t/iwillenshofer/ft_printf?color=brightgreen" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/iwillenshofer/ft_printf?color=brightgreen" />
</p>
<br>

> _This project is pretty straightforward, you have to recode printf. You will learn what is and how to implement variadic functions. Once you validate it, you will reuse this function in your future projects._

[Download the Subject ⤓](en.subject.pdf)

<br>

<p align="center">
	<table>
		<tr>
			<td><b>Est. Time</b></td>
			<td><b>Skills</b></td>
			<td><b>Allowed Functions</b></td>
			<td><b>Difficulty</b></td>
		</tr>
		<tr>
			<td valign="top">70 hours</td>
			<td valign="top">
<img src="https://img.shields.io/badge/Algorithms & AI-555">
<img src="https://img.shields.io/badge/Rigor-555">
			</td>
			<td valign="top">
				<img src="https://img.shields.io/badge/malloc()-lightgrey">
				<img src="https://img.shields.io/badge/free()-lightgrey">
				<img src="https://img.shields.io/badge/write()-lightgrey">
				<img src="https://img.shields.io/badge/va_start()-lightgrey"><br>
				<img src="https://img.shields.io/badge/va_arg()-lightgrey">
				<img src="https://img.shields.io/badge/va_copy()-lightgrey">
				<img src="https://img.shields.io/badge/va_end()-lightgrey">
			</td>
			<td valign="top"> 882 XP</td>
		</tr>
	</table>
</p>

<br>

### Modified Version, includes:

```c
/*original printf with buffering*/
int	ft_printf(const char *str, ...);

/*allows specifying a file descriptor to print into*/
int	ft_dprintf(int fd, const char *str, ...);

/*stores into a designated pre-allocated buffer*/
int	ft_snprintf(char *dest, size_t size, const char *str, ...);

/*returns an allocated char* */
int	ft_asprintf(char **ret, const char *str, ...);

```

### Usage
```bash
# create a main file.
$ make
$ gcc main.c -L. -lftprintf
$ ./a.out
```

#### Example of main() file
```c
#include "ft_printf.h"

int	main(void)
{
	char *string = "number 10";
	int	number = 10;
	ft_printf("%s, %d\n", string, number);
	return (0);
}
```

### Flags

| Flag  | Description														 |
|-------|--------------------------------------------------------------------|
| **-** | Align replaced text to the left when enough width is given         |
| **0** | Add '0' as a padding character in numeric conversions              |
| **+** | Add a plus sign ('+') in the front of positive numeric conversions |
| **#** | Alternate input method for placeholder                             |

### Conversions

| Conversion | Description					|
|------------|------------------------------|
| **c**		 | int converted to ASCII char	|
| **s**		 | NULL - terminated string		|
| **%**		 | '%' char literal				|
| **p**		 | Pointer memory address		|
| **d, i**	 | int in decimal base			|
| **u**		 | unsigned int in decimal base	|
| **o**		 | unsigned int in octal base	|
| **x, X**	 | int in hex base				|
