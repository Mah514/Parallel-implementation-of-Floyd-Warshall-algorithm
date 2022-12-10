# include <cstdlib>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <vector>
# include <mpi.h>
#include <math.h>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

void printVector(vector<int> v){
	for(int i=0;i<v.size();++i)
		cout<<v[i]<<" ";
	cout<<"\n";
}

void print2d(vector<vector<int>> v){
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] <<" ";
        }
    cout<<"\n";
    }
}

int main ( int argc, char *argv[] ) {

  int id;  //process Id  (Rank in MPI)
  int numProcesses;
  double startTime, elapsedTime;

  //  Initialize MPI.
  MPI_Init ( &argc, &argv );  
  startTime = MPI_Wtime ( );
  
  //  Get the number of processes.
  MPI_Comm_size ( MPI_COMM_WORLD, &numProcesses );

  //  Get the individual process ID.
  MPI_Comm_rank ( MPI_COMM_WORLD, &id );
  MPI_Status status;

  //Consts
  static const int INF = (INT_MAX - 2)/2;
  static const int n = 36;
  static const int sqrtp = sqrt(numProcesses);

  //Initial Send Array
  vector<int> sendRowBuff; // Array containing k'th column sent across a row
  vector<int> sendColBuff; // Array containing k'th row sent across a column

  // Initialise Receive Buffer on All processes
  vector<vector<int>> recvBuff;

  // Final vector
  vector<vector<int>> finalBuff;

  if (id == 0){
    vector<vector<int>> input{
      {0,   1, INF, INF,   4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF,   0,   2, INF,   3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF,   0,   3,   2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF,   0,   4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF,   0,   5,   2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,  20, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
     { 6, INF, INF, INF, INF,   0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF,   0,   1, INF, INF, INF, INF,   6, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF,   0,   2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF,   0,   3,   2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF,   6, INF,   3, INF, INF,   0,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   2, INF,   3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   5, INF, INF, INF, INF, INF,  10, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   6, INF, INF, INF, INF,   0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0, INF,   2, INF, INF,   6, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   5,   0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   4,   0, INF,   2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   3,   0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,  14},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   2,   0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   2,   1,   0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
     {25, INF, INF,  10, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   2, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   1,   2, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   3, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   4,   3, INF, INF,   0, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0, INF, INF, INF, INF,   6, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   2,   5,   0, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   4,   0, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   2,   3,   0, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   2,   0, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   3, INF,   1,   0, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1,   0}
	};

    //Mapping to grid algorithm
    for (int i = 1; i < numProcesses; i++){
        int row_id = i/sqrtp;
        int col_id = i%sqrtp;
        int starting_row = row_id*(n/sqrtp);
        int end_row = (row_id+1)*(n/sqrtp)-1;
        int starting_col = col_id*(n/sqrtp);
        int end_col = (col_id+1)*(n/sqrtp)-1;

        int target_id = (row_id*sqrtp) + col_id;

        for (int j = starting_row; j <= end_row; j++){
            vector<int> sendBuff;
            sendBuff = {input[j].begin() + starting_col, input[j].begin() + end_col + 1};
            MPI_Send(sendBuff.data(), sendBuff.size(), MPI_INT, target_id, 0, MPI_COMM_WORLD);
        }
    }

    recvBuff.resize(n/sqrtp);
    for (int i = 0; i < n/sqrtp; i++){
        recvBuff[i].resize(n/sqrtp);
    }
    int end_row = n/sqrtp-1;
    for (int i = 0; i <= end_row; i++){
        recvBuff[i] = {input[i].begin(), input[i].begin() + end_row + 1};
    }
  }
  else{
    recvBuff.resize(n/sqrtp);
    for (int i = 0; i < n/sqrtp; i++){
        recvBuff[i].resize(n/sqrtp);
    }
    for (int i = 0; i < n/sqrtp; i++){
        MPI_Recv(recvBuff[i].data(), recvBuff.size(), MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
  }

  // Floyd's parallel algorithm

  // Split the communicator
  MPI_Comm row_comm;
  MPI_Comm col_comm;
  MPI_Comm_split(MPI_COMM_WORLD, id/sqrtp, id, &row_comm);
  MPI_Comm_split(MPI_COMM_WORLD, id%sqrtp, id, &col_comm);
  int row_rank, row_size;
  int col_rank, col_size;
  MPI_Comm_rank(row_comm, &row_rank);
  MPI_Comm_size(row_comm, &row_size);
  MPI_Comm_rank(col_comm, &col_rank);
  MPI_Comm_size(col_comm, &col_size);

  for (int k = 0; k < n; k++){
    sendColBuff.clear();
    sendRowBuff.clear();
    int root = k/(n/sqrtp);
    int mod = n/sqrtp;

    if (row_rank == root){
      // Add the k'th row
      for(int row = 0; row < n/sqrtp; row++){
        for(int col = 0; col < n/sqrtp; col++){
          if(col == k%mod){
            sendColBuff.push_back(recvBuff[row][col]);
          }
        }
      }
    }
    else{
      sendColBuff.resize(n/sqrtp);
    }
    if (col_rank == root){
      // Add the k'th column
      for(int row = 0; row < n/sqrtp; row++){
        for(int col = 0; col < n/sqrtp; col++){
          if(col == k%mod){
            sendRowBuff.push_back(recvBuff[col][row]);
          }
        }
      }
    }
    else{
      sendRowBuff.resize(n/sqrtp);
    }

    MPI_Bcast(sendRowBuff.data(), sendRowBuff.size(), MPI_INT, root, col_comm);
    MPI_Bcast(sendColBuff.data(), sendColBuff.size(), MPI_INT, root, row_comm);
    
   
   for (int i = 0; i < n/sqrtp; i++){
    for (int j = 0; j < n/sqrtp; j++){
      if (recvBuff[i][j] > (sendColBuff[i] + sendRowBuff[j])){
        recvBuff[i][j] = (sendColBuff[i] + sendRowBuff[j]);
      }
    }
   }
  }
  
  // Merge results into output vector
  if (id == 0){
    finalBuff.resize(n);
    for (int i = 0; i < n; i++){
      finalBuff[i].resize(n);
    }
    for (int i = 0; i < recvBuff[0].size(); i++){
      for (int j = 0; j < recvBuff[0].size(); j++){
        finalBuff[i][j] = recvBuff[i][j];
      }
    }
  }

  if (id != 0){
    for (int i = 0; i < n/sqrtp; i++){
      MPI_Send(recvBuff[i].data(), recvBuff[i].size(), MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
  }
  
  if (id == 0){
    for (int i = 1; i < numProcesses; i++ ){
      int row_id = i/sqrtp;
      int col_id = i%sqrtp;
      int starting_row = row_id*(n/sqrtp);
      int end_row = (row_id+1)*(n/sqrtp)-1;
      int starting_col = col_id*(n/sqrtp);
      int end_col = (col_id+1)*(n/sqrtp)-1;

      int source_id = (row_id*sqrtp) + col_id;

      for (int j = starting_row; j <= end_row; j++){
        vector<int> tempBuff;
        tempBuff.resize(n/sqrtp);
        MPI_Recv(tempBuff.data(), tempBuff.size(), MPI_INT, source_id, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int c = starting_col; c <= end_col; c++){
          finalBuff[j][c] = tempBuff[c - starting_col];
        }
      }
      
    }
  }


  if (id == 0){
    print2d(finalBuff);
  }
  


  //  Terminate MPI.
  elapsedTime = MPI_Wtime ( ) - startTime;
  MPI_Finalize ( );

  //  Process 0 prints a termination message.
  if ( id == 0 )
  {
    //printVector(finalBuff);
    cout << "\nP" << id << ":    Elapsed time = " << elapsedTime << " seconds.\n";	
    cout << "P" << id << ":    Normal end of execution.\n";
  }

  return 0;
}

