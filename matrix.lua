local M = {
    { 3.4, 2.0, 2.0},
    {-3.5, 3.3, 0.5},
    { 0.1, 0.1, 3.3}
}

print(M[1][1].." "..M[1][2].." "..M[1][3])
print(M[2][1].." "..M[2][2].." "..M[2][3])
print(M[3][1].." "..M[3][2].." "..M[3][3])


-- Create a new Table
mat = {}

-- Initialize matrix dimensions
M =  3 -- number of columns in matrix
N =  2 -- number of rows in matrix

-- Initialize the table as a zero-matrix of size M x N
for i = 1,N do
    mat[i] = {}
    for j = 1, M do
        mat[i][j] = 0
    end
end
