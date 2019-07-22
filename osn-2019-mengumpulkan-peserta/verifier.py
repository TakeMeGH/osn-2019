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

  maxR = 100000
  maxRTimesC = 100000

  if subtask == 3:
    maxR = 1
    maxRTimesC = 2000

  if subtask == 4:
    maxR = 1

  if subtask == 5:
    maxRTimesC = 200

  if subtask == 6:
    maxRTimesC = 2000

  R = vr.ReadInt(1, maxR)
  assert vr.ReadChar() == ' ', 'Input is not space separated.'
  C = vr.ReadInt(1, maxRTimesC)
  assert R * C <= maxRTimesC, 'The value of R * C exceeds the limit.'
  vr.ReadEndl()

  S = []
  for _ in range(R):
    S.append(vr.ReadString(valid_characters='01', inc_min_len=C, inc_max_len=C))
    vr.ReadEndl()

  oneExists = False
  for s in S:
    for c in s:
      oneExists |= (c == '1')

  assert oneExists, 'S does not contain 1.'

  if subtask == 1:
    assert (R == 10 and C == 10 and
            S == ["0000000001",
                  "0010000100",
                  "0110111000",
                  "0111111000",
                  "0111111001",
                  "0101111000",
                  "0110111010",
                  "0110101000",
                  "0111111000",
                  "0000000000"]), 'Input does not satisfy open subtask 1.'

  if subtask == 2:
    assert (R == 10 and C == 10 and
            S == ["0101010101",
                  "1010101010",
                  "0101010101",
                  "1010101010",
                  "0101010101",
                  "1010101010",
                  "0101010101",
                  "1010101010",
                  "0101010101",
                  "1010101010"]), 'Input does not satisfy open subtask 2.'

  vr.ReadEof()


if __name__ == "__main__":
  sys.exit(main(sys.argv))
