class Node:
    some_word_ended_here = False

    A = None
    C = None
    U = None
    T = None

    def insert_string(self, string, k):

        if len(string) == k:
            if self.some_word_ended_here:
                return True

            self.some_word_ended_here = True
            return False

        letter = string[k]
        k = k+1

        if letter == 'A':
            if self.A is None:
                self.A = Node()
            return self.A.insert_string(string, k)
        elif letter == 'C':
            if self.C is None:
                self.C = Node()
            return self.C.insert_string(string, k)
        elif letter == 'U':
            if self.U is None:
                self.U = Node()
            return self.U.insert_string(string, k)
        elif letter == 'T':
            if self.T is None:
                self.T = Node()
            return self.T.insert_string(string, k)
        else:
            print("Invalid letter")


def main():
    words = ["ACA", "ACU", "ATA", "AC", "ACA"]

    root = Node()

    for word in words:
        if root.insert_string(word, 0):
            print("Duplicated word: " + word)


main()
