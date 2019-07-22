import re
import string
import sys


class VerifierReader(object):
  def __init__(self, text):
    self.text = text
    self.position = 0

  def HasNext(self):
    return self.position < len(self.text)

  def Read(self, target):
    actual = self.text[self.position : self.position + len(target)]
    assert actual == target, "Could not read '{0}'".format(target)
    self.position += len(target)

  def ReadEndl(self):
    self.Read('\n')

  def ReadEof(self):
    assert self.position == len(self.text), 'Found junk at the end of the file'

  def ReadChar(self):
    assert self.position < len(self.text), 'Unexpected EOF'
    char = self.text[self.position]
    self.position += 1
    return char

  def ReadLine(self, valid_characters):
    old_position = self.position
    while True:
      assert self.position < len(self.text), 'Unexpected EOF'
      c = self.text[self.position]
      self.position += 1
      if c == '\n':
        break
      assert c in valid_characters
    assert self.position - old_position > 1, 'Nothing before next newline'
    return self.text[old_position:self.position - 1]

  def ReadRegex(self, target_regex):
    match = re.compile(target_regex).match(self.text, self.position)
    assert match is not None, 'Could not match /%s/' % target_regex
    self.position = match.end()
    return match.group(0)

  def ReadList(self, n, read_fn, *args):
    ls = []
    for i in range(n):
      if i > 0:
        self.Read(' ')
      ls.append(read_fn())
    self.ReadEndl()
    return ls

  def ReadInt(self, inclusive_min, inclusive_max):
    value = int(self.ReadRegex(r'0|(-?[1-9][0-9]*)'))
    assert inclusive_min <= value <= inclusive_max, (
        'Failed on %d <= %d <= %d' % (inclusive_min, value, inclusive_max))
    return value

  def ReadIntList(self, n, inclusive_min, inclusive_max):
    return self.ReadList(n, lambda: self.ReadInt(inclusive_min, inclusive_max))

  def ReadString(self, valid_characters=string.ascii_letters + string.digits,
                 inc_min_len=1, inc_max_len=10**6):
    old_position = self.position
    while True:
      assert self.position < len(self.text), 'Unexpected EOF'
      c = self.text[self.position]
      if c not in valid_characters:
        break
      self.position += 1
    st = self.text[old_position:self.position]
    assert inc_min_len <= len(st) <= inc_max_len, (
        'Invalid string length: %d' % len(st))
    return st

  def ReadStringList(self, n,
                     valid_characters=string.ascii_letters + string.digits,
                     inc_min_len=1, inc_max_len=10**6):
    return self.ReadList(
        n,
        lambda: self.ReadString(valid_characters, inc_min_len, inc_max_len))


def main(argv):
  subtask = int(argv[1])
  assert 1 <= subtask <= 7
  vr = VerifierReader(sys.stdin.read())

  maxN = 200000
  maxM = 10**9

  if subtask == 3:
    maxN = 200
    maxM = 400

  if subtask == 4:
    maxN = 2000

  if subtask == 5:
    maxM = 400000  

  N = vr.ReadInt(1, maxN)
  assert vr.ReadChar() == ' ', 'Input is not space separated.'
  M = vr.ReadInt(1, maxM)
  vr.ReadEndl()
  
  A, B = [], []
  
  for _ in range(N):
    A.append(vr.ReadInt(1, maxM))
    assert vr.ReadChar() == ' ', 'Input is not space separated.'
    B.append(vr.ReadInt(A[-1], maxM))
    vr.ReadEndl()
  
  if subtask == 1:
    assert N == 8 and M == 11 and \
           A == [1, 4, 2, 9, 7, 2, 2, 8] and \
           B == [7, 11, 4, 10, 11, 4, 8, 8], \
           'Input does not satisfy open subtask 1.'
           
  if subtask == 2:
    assert N == 20 and M == 20 and \
           A == [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20] and \
           B == [20, 20, 18, 20, 20, 18, 14, 16, 18, 20, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20], \
           'Input does not satisfy open subtask 2.'

  if subtask == 6:
    overlap = 0
    for _, state in sorted([(a, -1) for a in A] + [(b, 1) for b in B]):
      overlap -= state
      assert overlap <= 2, 'Input does not satisfy subtask 6.'

  vr.ReadEof()


if __name__ == '__main__':
  sys.exit(main(sys.argv))
