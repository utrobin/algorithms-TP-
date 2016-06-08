// stable, 2-3 compares, 0-2 swaps
unsigned
sort3(BlackInt *x, BlackInt *y, BlackInt *z)
{
	if (*x <= *y) {
		if (*y <= *z)
			return 0;
		std::swap(*y, *z);
		if (*x > *y) {
			std::swap(*x, *y);
			return 2;
		}
		return 1;
	}
	if (*y > *z) {
		std::swap(*x, *z);
		return 1;
	}
	std::swap(*x, *y);
	if (*y > *z) {
		std::swap(*y, *z);
		return 2;
	}
	return 1;
}

// stable, 4-5 compares, 0-4 swaps
unsigned
sort4(BlackInt *x1, BlackInt *x2, BlackInt *x3, BlackInt *x4)
{
	unsigned r = sort3(x1, x2, x4);
	if (*x2 <= *x3) {
		if (*x3 <= *x4)
			return r;
		std::swap(*x3, *x4);
		return r + 1;
	}
	std::swap(*x2, *x3);
	if (*x1 <= *x2)
		return r + 1;
	std::swap(*x1, *x2);
	return r + 2;
}

// stable, 6-7 compares, 0-6 swaps
unsigned
sort5(BlackInt *x1, BlackInt *x2, BlackInt *x3, BlackInt *x4, BlackInt *x5)
{
	unsigned r = sort4(x1, x2, x4, x5);
	if (*x2 <= *x3) {
		if (*x3 <= *x4)
			return r;
		std::swap(*x3, *x4);
		if (*x4 <= *x5)
			return r + 1;
		std::swap(*x4, *x5);
		return r + 2;
	}
	std::swap(*x2, *x3);
	if (*x1 <= *x2)
		return r + 1;
	std::swap(*x1, *x2);
	return r + 2;
}

bool
insertion_sort_incomplete(BlackInt *first, BlackInt *last)
{
	switch (last - first) {
		case 0:
		case 1:
			return true;;
		case 2:
			if (*--last < *first)
				std::swap(*first, *last);
			return true;
		case 3:
			sort3(first, first + 1, --last);
			return true;
		case 4:
			sort4(first, first + 1, first + 2, --last);
			return true;
		case 5:
			sort5(first, first + 1, first + 2, first + 3, --last);
			return true;
	}
	BlackInt *j = first + 2;
	sort3(first, first + 1, j);
	const unsigned limit = 8;
	unsigned count = 0;
	for (BlackInt *i = j + 1; i != last; ++i) {
		if (*i < *j) {
			BlackInt t(std::move(*i));
			BlackInt *k = j;
			j = i;
			do {
				*j = std::move(*k);
				j = k;
			} while (j != first && t < *--k);
			*j = std::move(t);
			if (++count == limit) {
				return ++i == last;
			}
		}
		j = i;
	}
	return true;
}
//
void
sort(BlackInt *first, BlackInt *last)
{
	while (true) {
	restart:
		long long len = last - first;
		switch (len) {
			case 0:
			case 1:
				return;
			case 2:
				if (*--last < *first)
					std::swap(*first, *last);
				return;
			case 3:
				sort3(first, first + 1, --last);
				return;
			case 4:
				sort4(first, first + 1, first + 2, --last);
				return;
			case 5:
				sort5(first, first + 1, first + 2, first + 3, --last);
				return;
		}
		BlackInt *median = first;
		unsigned swaps;
		{
			long long delta;
			if (len > 96) {
				delta = len / 2;
				median += delta;
				delta /= 2;
				swaps = sort5(first, first + delta, median, median + delta, last - 1);
			} else {
				delta = len / 2;
				median += delta;
				swaps = sort3(first, median, last - 1);
			}
		}

		BlackInt *i = first;
		BlackInt *j = last;
		if (*i >= *median) {
			while (true) {
				if (i == --j) {
					++i;
					j = last;
					if (*first >= *--j) {
						while (true) {
							if (i == j)
								return;
							if (*first < *i) {
								std::swap(*i, *j);
								++swaps;
								++i;
								break;
							}
							++i;
						}
					}
					if (i == j)
						return;
					while (true) {
						while (*first >= *i) ++i;
						while (*first < *--j);
						if (i >= j)
							break;
						std::swap(*i, *j);
						++swaps;
						++i;
					}
					first = i;
					goto restart;
				}
				if (*j < *median) {
					std::swap(*i, *j);
					++swaps;
					break;
				}
			}
		}

		++i;
		if (i < j) {
			while (true) {
				while (*i < *median) ++i;
				while (*--j >= *median);
				if (i > j)
					break;
				std::swap(*i, *j);
				++swaps;
				if (median == i)
					median = j;
				++i;
			}
		}

		if (i != median && *median < *i) {
			std::swap(*i, *median);
			++swaps;
		}

		if (swaps == 0) {
			bool fs = insertion_sort_incomplete(first, i);
			if (insertion_sort_incomplete(i + 1, last)) {
				if (fs)
					return;
				last = i;
				continue;
			} else {
				if (fs) {
					first = ++i;
					continue;
				}
			}
		}

		if (i - first < last - i) {
			sort(first, i);
			first = ++i;
		} else {
			sort(i + 1, last);
			last = i;
		}
	}
}
