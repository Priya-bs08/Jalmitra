import csv
import pathlib
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]
DATA_FILE = ROOT / "data" / "sample_sensor_data.csv"

class SampleDataTests(unittest.TestCase):
    def test_csv_has_required_columns(self):
        with DATA_FILE.open(newline="", encoding="utf-8") as handle:
            reader = csv.DictReader(handle)
            self.assertEqual(
                reader.fieldnames,
                ["timestamp_s", "depth_m", "battery_v", "command",
                 "debris_collected_g", "notes"]
            )
            rows = list(reader)
        self.assertGreater(len(rows), 0)

    def test_sample_values_are_parseable(self):
        with DATA_FILE.open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                self.assertGreaterEqual(float(row["timestamp_s"]), 0)
                self.assertGreaterEqual(float(row["depth_m"]), 0)
                self.assertGreater(float(row["battery_v"]), 0)
                self.assertIn(row["command"], {"F", "B", "L", "R", "S"})
                self.assertGreaterEqual(float(row["debris_collected_g"]), 0)

if __name__ == "__main__":
    unittest.main()
