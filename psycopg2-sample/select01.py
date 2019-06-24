#!/usr/bin/env python3

import os
import psycopg2

def get_connection():
    dsn = os.environ.get('DATABASE_URL')
    return psycopg2.connect(dsn)

def main():
    with get_connection() as conn:
        with conn.cursor() as cur:
            cur.execute('''SELECT year, monthday, jyocd, kaiji, nichiji, racenum, hondai FROM n_race WHERE datakubun='7' ORDER BY year DESC, jyocd DESC, nichiji DESC, racenum DESC LIMIT 1000 ''')
            for row in cur:
                print(row)

if __name__ == "__main__":
    main()
