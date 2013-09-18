# CS645 - Project 3
* Dustin Ingram
* Ryan Peterson
* Joe Ruether

## Background
The basis behind the security vulnerability in this exercise is that one time
pads were used more than once to encrypt two different plaintext messages with
the same encryption key.

Six messages were encrypted with three different keys. Because of the
properties of XOR, it is possible to recover the plaintext messages by solving
pieces of the other pair and comparing the results.

## Determining Pad-Sharing
The first step in breaking the encryption is to determine which message pairs
were encrypted with the same keys.

We knew from the hints that the messages would be composed of English words and
phrases, which means all of the characters would likely be considered
"printable", and a majority of the characters would be lowercase ASCII
characters and basic punctuation marks.

A brute force method was used to XOR every possible pair of encrypted messages
with each other (resulting in the "encrypted pairwise XOR"), and the results
were sorted based on the number of printable characters when the encrypted
pairwise XOR was in turn XOR'd with various random strings of lowercase ASCII
characters.

Of all the combinations, it appeared that:
* ct1 and ct3 shared a pad;
* ct2 and ct5 shared a pad;
* ct4 and ct6 shared a pad.

Now that the messages were paired up, their respective encrypted pairwise XORs
were stored as separate files.

## Crib Dragging
The next step was to try and discover words that when XOR'd with one message
produce readable sequences at the same index in the other message. This is a
method known as "crib dragging".

The 100 most common words from the English language were pulled off of
Wikipedia into a list. For each word in the list (called the "crib"), the crib
was surrounded by spaces and XOR'd with the key at each index in the
128-character string. This is the "dragging" part.

The result was then filtered for results that were printable sequences and
contained mostly lowercase letters and common punctuation, and then examined by
hand for recognizable word fragments.

### Solving ct1 and ct3
The common word ` make ` (spaces included) was found to produce the word
`hearts` in the message.

The next step is to "expand" the crib. This uses the result found in the
previous step to get a longer match.  Essentially, the method involves flip
flopping between each message to find longer matches until the entire message
has been solved.

The fragment ` hearts ` was then searched, surrounded by spaces, to return the
corresponding `d make i` string in the other message.

From here a full dictionary of words was used to brute force the next string.
Every word that begins with the letter `i` was used to complete the word and
the result was filtered for printable strings.

In this case, the string `d make interesting` resulted in `hearts in love use`.
From here, Google was able to find the rest of the quote, and both plaintext
messages were solved.

For the other challenges, the use of punctuation was modified to include common
characters used in computer code, as the hint suggested.

### Solving ct2 and ct5
The fact that in ASCII, bit number 6 for letters is set, but is clear for
spaces, was also used to attempt to determine where the spaces were potentially
located.

This allowed the string `The Beatles` to be found at the end of one of the
messages, because its counterpart message was composed of spaces for that
section.

After finding the string `a secret` in the same message as `The Beatles`, some
lyric searching was able to determine the full message and solve the challenge.

### Solving ct4 and ct6
For the final challenge, the tip off that lead to the solution was discovering
that the word ` yourself ` resulted in ` printf("b`.

This revealed that the message was composed of C/C++ code and prompted
modifying the filter to include punctuation such as `(){}[];*!<>` to yield more
results.

## Tools Used
Python was used for the brute force and crib dragging scripts, which you can
find attached as `rank_xors.py` and `search.py`. Both include comments and
walk-throughs which explain how the scripts were used.
