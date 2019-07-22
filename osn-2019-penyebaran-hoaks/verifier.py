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
  maxS = 10**9
  maxSumO = 200000

  if subtask == 3:
    maxN = 50
    maxS = 50
    maxSumO = 50

  if subtask == 4:
    maxN = 50
    maxSumO = 50

  if subtask == 5:
    maxN = 200
    maxSumO = 200

  if subtask == 6:
    maxN = 2000
    maxSumO = 2000

  N = vr.ReadInt(1, maxN)
  assert vr.ReadChar() == ' ', 'Input is not space separated.'
  S = vr.ReadInt(1, maxS)
  assert vr.ReadChar() == ' ', 'Input is not space separated.'
  Q = vr.ReadInt(1, N)
  vr.ReadEndl()

  ABs = []
  sumO = 0
  for _ in range(N):
    O = vr.ReadInt(1, S)
    sumO += O

    assert vr.ReadChar() == ' ', 'Input is not space separated.'
    
    AB = vr.ReadIntList(2 * O, 1, S)
    for j in range(O):
      assert AB[2 * j] <= AB[2 * j + 1], 'A[i][j] > B[i][j].'
      if j > 0:
        assert AB[2 * j - 1] < AB[2 * j], 'B[i][j - 1] >= A[i][j].'

    ABs.append(AB)

  assert sumO <= maxSumO, 'Sum of O[i] exceeds the limit.'

  P = []
  lastPValue = 0
  for _ in range(Q):
    lastPValue = vr.ReadInt(lastPValue + 1, N)
    P.append(lastPValue)
    vr.ReadEndl()

  if subtask == 1:
    assert (N == 5 and S == 10 and Q == 2 and
            ABs == [[1, 3, 9, 10], [5, 6], [5, 6], [4, 4], [4, 4, 7, 9]] and
            P == [1, 2]), 'Input does not satisfy open subtask 1.'

  if subtask == 2:
    assert (N == 10 and S == 10 and Q == 5 and
            ABs == [[2, 2, 4, 4, 6, 6, 8, 8, 10, 10]] +
                   [[i, i] for i in range(2, 11)] and
            P == [1, 5, 6, 8, 9]), 'Input does not satisfy open subtask 2.'

  vr.ReadEof()


if __name__ == "__main__":
  sys.exit(main(sys.argv))
