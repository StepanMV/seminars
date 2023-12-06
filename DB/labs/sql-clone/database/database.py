import os

class Database:
    def __init__(self, db_name: str, read: bool = False):
        self.db_name = db_name
        self.filepath = f"data/{db_name}.csv"
        self.columns = []
        self.column_types = []
        self.data = {}
        self.current_id = 0
        if os.path.isfile(self.filepath) and read:
            self._read_file()
    
    def __repr__(self):
        return_str = f"Database at {self.filepath}\n"
        for id, row_dict in self.data.items():
            return_str += f"{id}: {row_dict}\n"
        return return_str
    
    def create(self, columns: list, column_types: list):
        self.columns += columns
        self.column_types += column_types
    

    def _fix_types(self, row_dict: dict):
        for column, column_type in zip(self.columns, self.column_types):
            if column_type == "int":
                row_dict[column] = int(row_dict.get(column, 0))
            elif column_type == "float":
                row_dict[column] = float(row_dict.get(column, 0))
            elif column_type == "bool":
                row_dict[column] = bool(int(row_dict.get(column, False)))
            else:
                row_dict[column] = row_dict.get(column, "")
        return row_dict
    
    def _fix_types_update(self, row_dict: dict):
        for column, column_type in zip(self.columns, self.column_types):
            if column in row_dict:
                if column_type == "int":
                    row_dict[column] = int(row_dict[column])
                elif column_type == "float":
                    row_dict[column] = float(row_dict[column])
                elif column_type == "bool":
                    row_dict[column] = bool(int(row_dict[column]))
        return row_dict
    
    def _read_file(self):
        with open(self.filepath, "r") as f:
            self.columns = f.readline().strip().split(",")
            self.column_types = f.readline().strip().split(",")
            if len(self.columns) != len(self.column_types):
                raise ValueError("Number of columns and column types do not match")
            for line in f.readlines():
                row_dict = {column: value for column, value in zip(self.columns, line.strip().split(","))}
                self.insert(row_dict)
    
    def save(self):
        with open(self.filepath, "w") as f:
            f.write(",".join(self.columns) + "\n")
            f.write(",".join(self.column_types) + "\n")
            for row in self.data.values():
                f.write(",".join([str(row[column]) for column in self.columns]) + "\n")

    def insert(self, row_dict: dict):
        row_dict = self._fix_types(row_dict)
        self.data.update({self.current_id: row_dict})
        self.current_id += 1
    
    def update(self, row_id: int, row_dict: dict):
        row_dict = self._fix_types_update(row_dict)
        self.data[row_id].update(row_dict)
    
    def delete(self, row_id: int):
        self.data.pop(row_id)
    
    def get(self, row_id: int):
        print(self.data[row_id])
                