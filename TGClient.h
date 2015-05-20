//
//  TGClient.h
//  https://github.com/tagyro/TGS
//

#import <Foundation/Foundation.h>

#import "Tolo.h"

#import "JSONModel.h"

#import "JSONHTTPClient.h"

@interface BasicEvent : NSObject
@property (strong, nonatomic) NSError *error;
@end

@interface LoginEvent : BasicEvent

@end

/*
 
 Session
 
 "id":"d646f602-6722-5b62-bb39-2900914bb340",
 "session_token":"fjBeO1FvXnFTaVF5fG1LaEpjWS0="
 
 */

@interface TGSession : JSONModel
@property (strong, nonatomic) NSString *sessionId;
@property (strong, nonatomic) NSString *sessionToken;
@end

/*
 
 User
 
 "id":1,
 "user_name":"Demo User",
 "first_name":"John",
 "last_name":"Smith",
 "email":"j8s@m.o",
 "last_login":"0000-01-01T00:00:00Z",
 "enabled":true,
 "created_at":"2015-03-20T18:15:40.8+01:00",
 "updated_at":"2015-03-20T18:15:40.8+01:00"
 
 */

@interface TGUser : JSONModel

@property (assign, nonatomic) int user_id;
@property (strong, nonatomic) NSString<Optional> *custom_id;
@property (strong, nonatomic) NSString *user_name;
@property (strong, nonatomic) NSString *first_name;
@property (strong, nonatomic) NSString *last_name;
@property (strong, nonatomic) NSString *email;
@property (strong, nonatomic) NSString<Optional> *password;
@property (strong, nonatomic) NSDate<Optional> *last_login;
@property (assign, nonatomic) bool enabled;
@property (strong, nonatomic) NSDate<Optional> *created_at;
@property (strong, nonatomic) NSDate<Optional> *updated_at;
@property (strong, nonatomic) NSString <Optional> *session_token;
//
@property (assign, nonatomic) bool activated;
@end

/*
 
 Connection
 
 "user_from_id":1,
 "user_to_id":3,
 "type":"follow",
 "enabled":true,
 "created_at":"2015-03-21T09:22:10.5+01:00",
 "updated_at":"2015-03-21T09:22:10.5+01:00"
 
 */

@interface TGConnection : JSONModel

@property (assign, nonatomic) int userFromId;
@property (assign, nonatomic) int userToId;
@property (strong, nonatomic) NSString *type;
@property (assign, nonatomic) BOOL enabled;
@property (assign, nonatomic) NSDate *createdAt;
@property (assign, nonatomic) NSDate *updatedAt;
@end

@interface TGDisplay : JSONModel

@end

/*
 
 Object
 
 "object":{
 "id":"picture1",
 "type":"picture",
 "display_name":TGDisplay
 }
 
 */

@interface TGObject : JSONModel
@property (assign, nonatomic) int object_id;
@property (strong, nonatomic) NSString *type;
@property (strong, nonatomic) TGDisplay *displayName;
@end

/*
 
 Event
 
 "id":1,
 "user_id":1,
 "verb":"like",
 "object":TGObject,
 "metadata":{
 "category":"landscape"
 },
 "enabled":true,
 "created_at":"2015-03-21T14:28:02.4+01:00",
 "updated_at":"2015-03-21T14:28:02.4+01:00"
 
 */

@interface TGEvent : JSONModel
@property (assign, nonatomic) int eventId;
@property (assign, nonatomic) int userId;
@property (strong, nonatomic) NSString<Optional> *verb;
@property (strong, nonatomic) NSString<Optional> *language;
@property (strong, nonatomic) NSString<Optional> *priority;
@property (strong, nonatomic) NSString<Optional> *location;
@property (assign, nonatomic) double latitude;
@property (assign, nonatomic) double longitude;
@property (strong, nonatomic) TGObject<Optional> *metadata;
@property (strong, nonatomic) TGObject<Optional> *object;

@end

@interface TGClient : NSObject
// Should be called once before first getting sharedClient
+ (void)setAPIKey:(NSString *)apiKey;
+ (id)sharedClient;

@property (strong) TGSession *session;
@property (strong) TGUser *me;

- (void)loginUser:(TGUser*)user;
- (void)createUser:(TGUser*)user;

- (void)createEvent:(TGEvent*)event;
- (void)deleteEvent:(TGEvent*)event;
- (void)updateEvent:(TGEvent*)event;
- (void)getEvent:(TGEvent*)event;
- (void)getFeed;

- (void)createConnection:(TGConnection*)connection;
- (void)deleteConnection:(TGConnection*)connection;
- (void)getFollowed:(TGUser*)user;
- (void)getFollowers:(TGUser*)user;
- (void)getFriends:(TGUser*)user;
@end


