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
  assert 1 <= subtask <= 10
  vr = VerifierReader(sys.stdin.read())

  R = vr.ReadInt(5, 1000)
  assert vr.ReadChar() == ' ', 'Input is not space separated.'
  C = vr.ReadInt(5, 1000)
  vr.ReadEndl()

  M = vr.ReadString(valid_characters='>v', inc_min_len=R+C-2, inc_max_len=R+C-2)
  vr.ReadEndl()

  S = []

  for _ in range(R):
    S.append(vr.ReadString(valid_characters='.#', inc_min_len=C, inc_max_len=C))
    vr.ReadEndl()

  vr.ReadEof()

  ## Validate route
  row, col = 0, 0
  assert S[0][0] == '.', 'Route is blocked.'

  for c in M:
    if c == '>':
      col += 1
      assert col < C, 'Route goes outside of grid.'
    if c == 'v':
      row += 1
      assert row < R, 'Route goes outside of grid.'
      
    assert S[row][col] == '.', 'Route is blocked.'
  ## End of route validation
  
  ## Utils for subtasks verifier
  empty_grid = lambda: S == ['.' * C] * R
  turns_once = lambda: M == '>' * (C-1) + 'v' * (R-1)
  ## End of subtasks verifier utils

  if subtask == 1:
    assert R == 6 and C == 6 and empty_grid(), \
          'Input does not satisfy subtask 1.'

  if subtask == 2:
    assert R == 5 and C == 7 and turns_once(), \
          'Input does not satisfy subtask 2.'

  if subtask == 3:
    assert R == 7 and C == 5, \
          'Input does not satisfy subtask 3.'

  if subtask == 4:
    assert R == 100 and C == 16, \
          'Input does not satisfy subtask 4.'

  if subtask == 5:
    assert R == 677 and C == 751 and empty_grid() and turns_once(), \
          'Input does not satisfy subtask 5.'

  if subtask == 6:
    assert R == 93 and C == 78 and empty_grid(), \
          'Input does not satisfy subtask 6.'

  if subtask == 7:
    assert R == 1000 and C == 1000 and empty_grid(), \
          'Input does not satisfy subtask 7.'

  if subtask == 8:
    assert R == 100 and C == 99 and turns_once(), \
          'Input does not satisfy subtask 8.'

  if subtask == 9:
    assert R == 853 and C == 814 and turns_once(), \
          'Input does not satisfy subtask 9.'

  if subtask == 10:
    assert R == 1000 and C == 1000 and turns_once(), \
          'Input does not satisfy subtask 10.'


if __name__ == '__main__':
  sys.exit(main(sys.argv))
