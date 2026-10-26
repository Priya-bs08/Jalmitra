import unittest

VALID_COMMANDS = {"F", "B", "L", "R", "S"}

def parse_command(raw):
    command = raw.strip().upper()
    return command if len(command) == 1 and command in VALID_COMMANDS else None

class CommandParsingTests(unittest.TestCase):
    def test_valid_commands(self):
        for command in VALID_COMMANDS:
            with self.subTest(command=command):
                self.assertEqual(parse_command(command), command)

    def test_whitespace_and_lowercase(self):
        self.assertEqual(parse_command(" f \n"), "F")

    def test_invalid_commands(self):
        for command in ("", "X", "FORWARD", "FF", "1"):
            with self.subTest(command=command):
                self.assertIsNone(parse_command(command))

if __name__ == "__main__":
    unittest.main()
