// Cycle.h
#ifndef CYCLE_H
#define CYCLE_H

class Cycle {
public:

    /// <summary>
    /// Reset the cycle and get it ready to start again
    /// </summary>
    virtual void Reset() = 0;

    /// <summary>
	/// Call repeatedly to perform the cycle's operation
    /// </summary>
    /// <returns>true if more steps remain (cycle is not done)</returns>
    virtual bool Update() = 0;

	/// <summary>
	/// Returns true if the cycle is in an error state
	/// </summary>
	virtual bool IsInError() = 0;

};

#endif // CYCLE_H