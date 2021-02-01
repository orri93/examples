import { User } from '../models/user';
import { UserActionTypes } from '../actions/user.actions';
import { createSelector } from '@ngrx/store';

export interface UserState {
  user: User;
}

const initialLoginState: UserState = {
  user: new User({
    uName: 'Guest',
    isAdmin: false,
    ts: mTstamp(),
    loggedIn: false
  })
};

export function userReducer(appUserState = initialLoginState, action): UserState {
  switch (action.type) {
    case UserActionTypes.ACTION_LOGOUT:
      return {
        ...appUserState,
        user: new User({
          uName: 'Guest',
          isAdmin: false,
          ts: mTstamp(), // its not a good practice generating timestamp in reducer. reducers are pure functions :)
          loggedIn: false
        })
      };
    case UserActionTypes.ACTION_LOGIN:
      return {
        ...appUserState,
        // user: new User({
        //   uName: action.payload,   //  <-- make sure which value is incoming.
        //                                    may be action.payload.uname based
        //                                    on which value you are dispatching
        //                                    from component.
        //   isAdmin: action.payload, //  <-- make sure which value is incoming.
        //   ts: action.payload,      //  <-- make sure which value is incoming.
        //   loggedIn: action.payload //  <-- make sure which value is incoming.
        // })

        user: new User({
          ...action.payload //  <-- make sure which value is incoming. 
        })
      };
  }
  return appUserState;
}

export const selectUserState = (state) => state.userState;
export const selectUser = createSelector(selectUserState, (state) => state.user);

// Move this as part for component or service.
export function mTstamp(): string {
  let d = new Date();
  let mMonth;
  if (d.getMonth() < 10) {
    mMonth = '0' + d.getMonth();
  } else {
    mMonth = d.getMonth();
  }
  let mDate;
  if (d.getDate() < 10) {
    mDate = '0' + d.getDate();
  } else {
    mDate = d.getDate();
  }
  let mHours;
  if (d.getHours() < 10) {
    mHours = '0' + d.getHours();
  } else {
    mHours = d.getHours();
  }
  let mMins;
  if (d.getMinutes() < 10) {
    mMins = '0' + d.getMinutes();
  } else {
    mMins = d.getMinutes();
  }
  let mSecs;
  if (d.getSeconds() < 10) {
    mSecs = '0' + d.getSeconds();
  } else {
    mSecs = d.getSeconds();
  }
  let mTimeStamp =
    d.getFullYear() +
    '-' +
    mMonth +
    '-' +
    mDate +
    ' ' +
    mHours +
    ':' +
    mMins +
    ':' +
    mSecs;
  console.log('mTimeStamp: ', mTimeStamp);
  return mTimeStamp;
}
