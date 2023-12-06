from database import Database
import re

dbs = {}

def parse_command(user_input: str):
    if user_input.startswith("CREATE TABLE"):
        template = re.compile(r"CREATE TABLE (\w+) \(([\w ,]+)\)")
        name, args = template.findall(user_input)[0]
        columns, column_types = [], []
        for arg in args.split(", "):
            column, column_type = arg.split(" ")
            columns.append(column)
            column_types.append(column_type)
        db = Database(name)
        dbs.update({name: db})
        if columns and column_types:
            db.create(columns, column_types)
        return True

    elif user_input.startswith("READ TABLE"):
        template = re.compile(r"READ TABLE (\w+)")
        name = template.findall(user_input)[0]
        db = Database(name, read=True)
        dbs.update({name: db})
        return True


    elif user_input.startswith("INSERT INTO"):
        template = re.compile(r"INSERT INTO (\w+) \(([\w ,]+)\) VALUES \(([\w ,]+)\)")
        name, keys, values = template.findall(user_input)[0]
        row_dict = {key: value for key, value in zip(keys.split(", "), values.split(", "))}
        dbs[name].insert(row_dict)
        return True

    elif user_input.startswith("UPDATE"):
        template = re.compile(r"UPDATE (\w+) ROW (\w+) \(([\w ,]+)\) VALUES \(([\w ,]+)\)")
        name, row_id, keys, values = template.findall(user_input)[0]
        row_dict = {key: value for key, value in zip(keys.split(", "), values.split(", "))}
        dbs[name].update(int(row_id), row_dict)
        return True

    elif user_input.startswith("DELETE FROM"):
        template = re.compile(r"DELETE FROM (\w+) ROW (\w+)")
        name, row_id = template.findall(user_input)[0]
        dbs[name].delete(int(row_id))
        return True

    elif user_input.startswith("SAVE"):
        template = re.compile(r"SAVE (\w+)")
        name = template.findall(user_input)[0]
        dbs[name].save()
        return True

    elif user_input.startswith("GET FROM"):
        template = re.compile(r"GET FROM (\w+) ROW (\w+)")
        name, row_id = template.findall(user_input)[0]
        dbs[name].get(int(row_id))
        return True
    
    elif user_input.startswith("PRINT"):
        template = re.compile(r"PRINT (\w+)")
        name = template.findall(user_input)[0]
        print(dbs[name])
        return True

    else:
        return False

if __name__ == '__main__':
    while parse_command(input()):
        pass