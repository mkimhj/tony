f = open("data.txt")
char_list = [line for line in f]
from collections import Counter

char_freq = Counter(char_list).most_common()
num_samples = 0
for ch in char_freq:
	if ch[0] == '___\n':
		num_samples = ch[1]


avg_char_freq = [(char_freq[i][0], char_freq[i][1] / (num_samples+1)) for i in range(0, len(char_freq))]

print(avg_char_freq)
print(num_samples+1)