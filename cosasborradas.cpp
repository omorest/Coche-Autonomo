// Only process this cell if this is a valid one
if (isValid(i - 1, j) == true)
{
	// If the destination cell is the same as the
	// current successor
	if (isDestination(i - 1, j, dest) == true)
	{
		// Set the Parent of the destination cell
		cellDetails[i - 1][j].SetParentActualX(i);
		cellDetails[i - 1][j].SetParentActualY(j);
		printf("The destination cell is found\n");

		TracePath(cellDetails, dest);
		foundDest = true;

		return;
	}
	// If the successor is already on the closed
	// list or if it is blocked, then ignore it.
	// Else do the following
	else if (closedList[i - 1][j] == false &&
			 isUnBlocked(grid, i - 1, j) == true)
	{
		gNew = cellDetails[i][j].GetG() + 1.0;
		hNew = calculateHValue(i - 1, j, dest);
		fNew = gNew + hNew;

		// If it isn’t on the open list, add it to
		// the open list. Make the current square
		// the parent of this square. Record the
		// f, g, and h costs of the square cell
		//			 OR
		// If it is on the open list already, check
		// to see if this path to that square is better,
		// using 'f' cost as the measure.
		if (cellDetails[i - 1][j].GetF() == FLT_MAX ||
			cellDetails[i - 1][j].GetF() > fNew)
		{
			openList.insert(make_pair(fNew,
									  make_pair(i - 1, j)));

			// Update the details of this cell
			cellDetails[i - 1][j].SetF(fNew);
			cellDetails[i - 1][j].SetG(gNew);
			cellDetails[i - 1][j].SetH(hNew);
			cellDetails[i - 1][j].SetParentActualX(i);
			cellDetails[i - 1][j].SetParentActualY(j);
		}
	}
}

//----------- 2nd Successor (South) ------------

// Only process this cell if this is a valid one
if (isValid(i + 1, j) == true)
{
	// If the destination cell is the same as the
	// current successor
	if (isDestination(i + 1, j, dest) == true)
	{
		// Set the Parent of the destination cell
		cellDetails[i + 1][j].SetParentActualX(i);
		cellDetails[i + 1][j].SetParentActualY(j);
		printf("The destination cell is found\n");
		TracePath(cellDetails, dest);
		foundDest = true;
		return;
	}
	// If the successor is already on the closed
	// list or if it is blocked, then ignore it.
	// Else do the following
	else if (closedList[i + 1][j] == false &&
			 isUnBlocked(grid, i + 1, j) == true)
	{
		gNew = cellDetails[i][j].GetG() + 1.0;
		hNew = calculateHValue(i + 1, j, dest);
		fNew = gNew + hNew;

		// If it isn’t on the open list, add it to
		// the open list. Make the current square
		// the parent of this square. Record the
		// f, g, and h costs of the square cell
		//			 OR
		// If it is on the open list already, check
		// to see if this path to that square is better,
		// using 'f' cost as the measure.
		if (cellDetails[i + 1][j].GetF() == FLT_MAX ||
			cellDetails[i + 1][j].GetF() > fNew)
		{
			openList.insert(make_pair(fNew, make_pair(i + 1, j)));
			// Update the details of this cell
			cellDetails[i + 1][j].SetF(fNew);
			cellDetails[i + 1][j].SetG(gNew);
			cellDetails[i + 1][j].SetH(hNew);
			cellDetails[i + 1][j].SetParentActualX(i);
			cellDetails[i + 1][j].SetParentActualY(j);
		}
	}
}

//----------- 3rd Successor (East) ------------

// Only process this cell if this is a valid one
if (isValid(i, j + 1) == true)
{
	// If the destination cell is the same as the
	// current successor
	if (isDestination(i, j + 1, dest) == true)
	{
		// Set the Parent of the destination cell
		cellDetails[i][j + 1].SetParentActualX(i);
		cellDetails[i][j + 1].SetParentActualY(j);
		printf("The destination cell is found\n");
		TracePath(cellDetails, dest);
		foundDest = true;
		return;
	}

	// If the successor is already on the closed
	// list or if it is blocked, then ignore it.
	// Else do the following
	else if (closedList[i][j + 1] == false &&
			 isUnBlocked(grid, i, j + 1) == true)
	{
		gNew = cellDetails[i][j].GetG() + 1.0;
		hNew = calculateHValue(i, j + 1, dest);
		fNew = gNew + hNew;

		// If it isn’t on the open list, add it to
		// the open list. Make the current square
		// the parent of this square. Record the
		// f, g, and h costs of the square cell
		//			 OR
		// If it is on the open list already, check
		// to see if this path to that square is better,
		// using 'f' cost as the measure.
		if (cellDetails[i][j + 1].GetF() == FLT_MAX ||
			cellDetails[i][j + 1].GetF() > fNew)
		{
			openList.insert(make_pair(fNew,
									  make_pair(i, j + 1)));

			// Update the details of this cell
			cellDetails[i][j + 1].SetF(fNew);
			cellDetails[i][j + 1].SetG(gNew);
			cellDetails[i][j + 1].SetH(hNew);
			cellDetails[i][j + 1].SetParentActualX(i);
			cellDetails[i][j + 1].SetParentActualY(j);
		}
	}
}

//----------- 4th Successor (West) ------------

// Only process this cell if this is a valid one
if (isValid(i, j - 1) == true)
{
	// If the destination cell is the same as the
	// current successor
	if (isDestination(i, j - 1, dest) == true)
	{
		// Set the Parent of the destination cell
		cellDetails[i][j - 1].SetParentActualX(i);
		cellDetails[i][j - 1].SetParentActualY(j);
		printf("The destination cell is found\n");
		TracePath(cellDetails, dest);
		foundDest = true;
		return;
	}

	// If the successor is already on the closed
	// list or if it is blocked, then ignore it.
	// Else do the following
	else if (closedList[i][j - 1] == false &&
			 isUnBlocked(grid, i, j - 1) == true)
	{
		gNew = cellDetails[i][j].GetG() + 1.0;
		hNew = calculateHValue(i, j - 1, dest);
		fNew = gNew + hNew;

		// If it isn’t on the open list, add it to
		// the open list. Make the current square
		// the parent of this square. Record the
		// f, g, and h costs of the square cell
		//			 OR
		// If it is on the open list already, check
		// to see if this path to that square is better,
		// using 'f' cost as the measure.
		if (cellDetails[i][j - 1].GetF() == FLT_MAX ||
			cellDetails[i][j - 1].GetF() > fNew)
		{
			openList.insert(make_pair(fNew,
									  make_pair(i, j - 1)));

			// Update the details of this cell
			cellDetails[i][j - 1].SetF(fNew);
			cellDetails[i][j - 1].SetG(gNew);
			cellDetails[i][j - 1].SetH(hNew);
			cellDetails[i][j - 1].SetParentActualX(i);
			cellDetails[i][j - 1].SetParentActualY(j);
		}
	}
}
