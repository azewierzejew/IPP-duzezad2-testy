for f in "$2"/*.in; do
	echo "Test $f"
	diff ${f%in}err <("$1" < "$f" 2>&1 >/dev/null) >/dev/null 2>/dev/null
	if (($?!=0)); then
		echo "Error on test $f (stderr)"
	fi
	diff ${f%in}out <("$1" < "$f" 2>/dev/null) >/dev/null 2>/dev/null
	if (($?!=0)); then
		echo "Error on test $f (stdout)"
	fi
	valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all "$1" < "$f" >/dev/null 2>/dev/null
	if (($?==1)); then
		echo "Memory management error on test $f (valgrind)"
	fi
done
	
